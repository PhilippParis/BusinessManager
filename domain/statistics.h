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

    /**
     * @return returns the total revenue
     */
    Decimal revenue() const;

    /**
     * @brief sets the total revenue
     * @param revenue revenue
     */
    void setRevenue(const Decimal &revenue);

    /**
     * @return returns the material expenses (incl taxes and overhead)
     */
    Decimal materialExpenses() const;

    /**
     * @brief sets the material expenses
     * @param materialExpenses material expenses (incl taxes and overhead)
     */
    void setMaterialExpenses(const Decimal &materialExpenses);

    /**
     * @return returns the sales tax expenses
     */
    Decimal salesTaxExpenses() const;

    /**
     * @brief sets the sales tax expenses
     * @param salesTax sales tax expenses
     */
    void setSalesTaxExpenses(const Decimal &salesTaxExpenses);

    /**
     * @return returns the revenue from pre tax
     */
    Decimal preTaxRevenue() const;

    /**
     * @brief sets the pre tax revenue
     * @param preTax pre tax revenue
     */
    void setPreTaxRevenue(const Decimal &preTaxRevenue);

    /**
     * @return returns the profit
     */
    Decimal profit() const;

    /**
     * @brief sets the profit
     * @param profit profit
     */
    void setProfit(const Decimal &profit);

    /**
     * @return returns the factory expenses (incl overhead)
     */
    Decimal factoryExpenses() const;

    /**
     * @brief sets the factory expenses
     * @param factoryExpenses factory expenses (incl overhead)
     */
    void setFactoryExpenses(const Decimal &factoryExpenses);

    /**
     * @return returns datapoints illustrating the history of expenses
     */

    QVector<double> dataPointsExpenses() const;
    /**
     * @brief sets the datapoints illustrating the history of revenue
     * @param dataPointsExpenses datapoints
     */
    void setDataPointsExpenses(const QVector<double> &dataPointsExpenses);

    /**
     * @return returns datapoints illustrating the history of revenue
     */
    QVector<double> dataPointsRevenue() const;

    /**
     * @brief sets the datapoints illustrating the history of revenue
     * @param dataPointsRevenue datapoints
     */
    void setDataPointsRevenue(const QVector<double> &dataPointsRevenue);

    /**
     * @return return a vector of dates (in juliandays)
     *         on which the datapoints were captured
     */
    QVector<double> dataPointsDates() const;

    /**
     * @brief sets the vector of dates
     * @param dataPointsDates dates on which the datapoints (revenue and expenses)
     *        were captured
     */
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
