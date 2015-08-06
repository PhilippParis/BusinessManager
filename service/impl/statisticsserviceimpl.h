#ifndef STATISTICSSERVICEIMPL_H
#define STATISTICSSERVICEIMPL_H

#include "persistence/billdao.h"

#include "service/statisticsservice.h"

class StatisticsServiceImpl : public StatisticsService
{
public:
    StatisticsServiceImpl(BillDAO::Ptr billDAO);
    Statistics::Ptr getStatistics(QDate from, QDate to) override;

private:
    Decimal factoryExpenses(Bill::Ptr bill);
    Decimal materialExpenses(Bill::Ptr bill);

    Decimal salesTax(Bill::Ptr bill);
    Decimal preTax(Bill::Ptr bill);

private:
    BillDAO::Ptr m_billDAO;
};

#endif // STATISTICSSERVICEIMPL_H
