#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <qwt/qwt.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_point_data.h>

#include "service/statisticsservice.h"
#include "service/billservice.h"

namespace Ui {
class StatisticsWidget;
}

class StatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = 0);
    ~StatisticsWidget();

    void setStatisticsService(StatisticsService::Ptr statisticsService);
    void setBillService(BillService::Ptr billService);

public slots:
    void update();

private:
    Ui::StatisticsWidget *ui;
    QwtPlot *m_plotWidget;
    QwtPlotCurve *m_expensesCurve;
    QwtPlotCurve *m_revenueCurve;

    StatisticsService::Ptr m_statisticsService;
    BillService::Ptr m_billService;
};

#endif // STATISTICSWIDGET_H
