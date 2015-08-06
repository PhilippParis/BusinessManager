#ifndef STATISTICS_H
#define STATISTICS_H

#include <memory>
#include <QVector>
#include <QDebug>
#include "decimal.h"

class Statistics
{
public:
    typedef std::shared_ptr<Statistics> Ptr;

    Statistics();

    Decimal totalRevenue() const;
    void setTotalRevenue(const Decimal &totalRevenue);

    Decimal materialExpenses() const;
    void setMaterialExpenses(const Decimal &materialExpenses);

    Decimal salesTax() const;
    void setSalesTax(const Decimal &salesTax);

    Decimal preTax() const;
    void setPreTax(const Decimal &preTax);

    Decimal profit() const;
    void setProfit(const Decimal &profit);

    Decimal factoryExpenses() const;
    void setFactoryExpenses(const Decimal &factoryExpenses);

    QVector<double> dataPointsExpenses() const;
    void setDataPointsExpenses(const QVector<double> &dataPointsExpenses);

    QVector<double> dataPointsRevenue() const;
    void setDataPointsRevenue(const QVector<double> &dataPointsRevenue);

    QVector<double> dataPointsDates() const;
    void setDataPointsDates(const QVector<double> &dataPointsDates);

private:
    QVector<double> m_dataPointsExpenses;
    QVector<double> m_dataPointsRevenue;
    QVector<double> m_dataPointsDates;

    Decimal m_totalRevenue;
    Decimal m_materialExpenses;
    Decimal m_factoryExpenses;
    Decimal m_salesTax;
    Decimal m_preTax;
    Decimal m_profit;
};

#endif // STATISTICS_H
