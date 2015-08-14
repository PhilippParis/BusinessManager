#include "statistics.h"

Statistics::Statistics()
{

}

Decimal Statistics::revenue() const
{
    return m_totalRevenue;
}

void Statistics::setRevenue(const Decimal &totalRevenue)
{
    m_totalRevenue = totalRevenue;
}
Decimal Statistics::materialExpenses() const
{
    return m_materialExpenses;
}

void Statistics::setMaterialExpenses(const Decimal &materialExpenses)
{
    m_materialExpenses = materialExpenses;
}

Decimal Statistics::salesTaxExpenses() const
{
    return m_salesTax;
}

void Statistics::setSalesTaxExpenses(const Decimal &salesTax)
{
    m_salesTax = salesTax;
}
Decimal Statistics::preTaxRevenue() const
{
    return m_preTax;
}

void Statistics::setPreTaxRevenue(const Decimal &preTax)
{
    m_preTax = preTax;
}
Decimal Statistics::profit() const
{
    return m_profit;
}

void Statistics::setProfit(const Decimal &profit)
{
    m_profit = profit;
}

Decimal Statistics::factoryExpenses() const
{
    return m_factoryExpenses;
}

void Statistics::setFactoryExpenses(const Decimal &factoryExpenses)
{
    m_factoryExpenses = factoryExpenses;
}
QVector<double> Statistics::dataPointsExpenses() const
{
    return m_dataPointsExpenses;
}

void Statistics::setDataPointsExpenses(const QVector<double> &dataPointsExpenses)
{
    m_dataPointsExpenses = dataPointsExpenses;
}
QVector<double> Statistics::dataPointsRevenue() const
{
    return m_dataPointsRevenue;
}

void Statistics::setDataPointsRevenue(const QVector<double> &dataPointsRevenue)
{
    m_dataPointsRevenue = dataPointsRevenue;
}
QVector<double> Statistics::dataPointsDates() const
{
    return m_dataPointsDates;
}

void Statistics::setDataPointsDates(const QVector<double> &dataPointsDates)
{
    m_dataPointsDates = dataPointsDates;
}














