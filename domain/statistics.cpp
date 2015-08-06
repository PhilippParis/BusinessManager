#include "statistics.h"

Statistics::Statistics()
{

}

Decimal Statistics::totalRevenue() const
{
    return m_totalRevenue;
}

void Statistics::setTotalRevenue(const Decimal &totalRevenue)
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

Decimal Statistics::salesTax() const
{
    return m_salesTax;
}

void Statistics::setSalesTax(const Decimal &salesTax)
{
    m_salesTax = salesTax;
}
Decimal Statistics::preTax() const
{
    return m_preTax;
}

void Statistics::setPreTax(const Decimal &preTax)
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














