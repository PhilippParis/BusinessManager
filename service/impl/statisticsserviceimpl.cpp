#include "statisticsserviceimpl.h"

StatisticsServiceImpl::StatisticsServiceImpl(BillDAO::Ptr billDAO)
 : m_billDAO(billDAO)
{

}

Statistics::Ptr StatisticsServiceImpl::getStatistics(QDate from, QDate to)
{
    QList<Bill::Ptr> bills = m_billDAO->get(from, to);
    Statistics::Ptr stats = std::make_shared<Statistics>();

    QVector<double> expensesDataPoints;
    QVector<double> revenueDataPoints;
    QVector<double> datesDataPoints;

    Decimal overallMaterialExpenses = Decimal::fromValue(0.0);
    Decimal overallFactoryExpenses = Decimal::fromValue(0.0);
    Decimal overallSalesTax = Decimal::fromValue(0.0);
    Decimal overallPreTax = Decimal::fromValue(0.0);
    Decimal overallRevenue = Decimal::fromValue(0.0);
    Decimal overallProfit = Decimal::fromValue(0.0);

    for (Bill::Ptr bill : bills) {
        overallMaterialExpenses += materialExpenses(bill);
        overallFactoryExpenses += factoryExpenses(bill);
        overallPreTax += preTax(bill);
        overallSalesTax += salesTax(bill);
        overallRevenue += bill->totalPrice();

        expensesDataPoints.append((overallMaterialExpenses + overallFactoryExpenses + overallSalesTax - overallPreTax).value());
        revenueDataPoints.append(overallRevenue.value());
        datesDataPoints.append(bill->date().toJulianDay());
    }

    overallProfit = overallRevenue - overallMaterialExpenses - overallFactoryExpenses - overallSalesTax + overallPreTax;

    stats->setPreTaxRevenue(overallPreTax);
    stats->setSalesTaxExpenses(overallSalesTax);
    stats->setMaterialExpenses(overallMaterialExpenses);
    stats->setFactoryExpenses(overallFactoryExpenses);
    stats->setRevenue(overallRevenue);
    stats->setProfit(overallProfit);

    stats->setDataPointsExpenses(expensesDataPoints);
    stats->setDataPointsRevenue(revenueDataPoints);
    stats->setDataPointsDates(datesDataPoints);

    return stats;
}

Decimal StatisticsServiceImpl::factoryExpenses(Bill::Ptr bill)
{
    Decimal factory = Decimal::fromValue(0.0);
    for (BillItem::Ptr item : bill->items()) {
        factory += item->factoryExpenses() * item->quantity();
    }

    return factory;
}

Decimal StatisticsServiceImpl::materialExpenses(Bill::Ptr bill)
{
    Decimal material = Decimal::fromValue(0.0);
    for (BillItem::Ptr item : bill->items()) {
        material += item->materialExpenses() * item->quantity();
    }

    return material;
}

Decimal StatisticsServiceImpl::salesTax(Bill::Ptr bill)
{
    Decimal tax = Decimal::fromValue(0.0);
    for (Decimal value : bill->inTotalPriceIncludedTaxes().values()) {
        tax += value;
    }

    return tax;
}

Decimal StatisticsServiceImpl::preTax(Bill::Ptr bill)
{
    Decimal tax = Decimal::fromValue(0.0);
    for (BillItem::Ptr item : bill->items()) {
        tax += (item->materialCost() - item->materialNetCost()) * item->quantity();
    }

    return tax;
}

