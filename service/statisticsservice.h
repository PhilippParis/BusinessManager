#ifndef STATISTICSSERVICE_H
#define STATISTICSSERVICE_H

#include <memory>
#include <QDate>

#include "domain/statistics.h"

class StatisticsService
{
public:
    typedef std::shared_ptr<StatisticsService> Ptr;
    StatisticsService();

    /**
     * @param from intervall start
     * @param to intervall end
     * @return returns statistics for the specified intervall
     */
    virtual Statistics::Ptr getStatistics(QDate from, QDate to) = 0;
};

#endif // STATISTICSSERVICE_H
