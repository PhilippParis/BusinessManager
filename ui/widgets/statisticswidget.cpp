#include "statisticswidget.h"
#include "ui_statisticswidget.h"

StatisticsWidget::StatisticsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWidget)
{
    ui->setupUi(this);

    m_plotWidget = new QwtPlot(this);
    m_plotWidget->enableAxis(QwtPlot::xBottom, false);
    m_plotWidget->setMaximumHeight(250);

    m_expensesCurve = new QwtPlotCurve(tr("Expenses"));
    m_expensesCurve->setPen(Qt::red, 1.5);
    m_expensesCurve->attach(m_plotWidget);

    m_revenueCurve = new QwtPlotCurve(tr("Revenue"));
    m_revenueCurve->setPen(Qt::blue, 1.5);
    m_revenueCurve->attach(m_plotWidget);

    m_expensesCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    m_revenueCurve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    ui->verticalLayout->insertWidget(0, m_plotWidget);

    connect(ui->dateTo, SIGNAL(dateChanged(QDate)), SLOT(update()));
    connect(ui->dateFrom, SIGNAL(dateChanged(QDate)), SLOT(update()));
}

StatisticsWidget::~StatisticsWidget()
{
    delete ui;
}

void StatisticsWidget::setStatisticsService(StatisticsService::Ptr statisticsService)
{
    m_statisticsService = statisticsService;
    update();
}

void StatisticsWidget::setDateFilter(QDate from, QDate to)
{
    ui->dateFrom->setDate(from);
    ui->dateTo->setDate(to);
}

void StatisticsWidget::update()
{
    Statistics::Ptr stats = m_statisticsService->getStatistics(ui->dateFrom->date(), ui->dateTo->date());
    m_expensesCurve->setSamples(new QwtPointArrayData(stats->dataPointsDates(), stats->dataPointsExpenses()));
    m_revenueCurve->setSamples(new QwtPointArrayData(stats->dataPointsDates(), stats->dataPointsRevenue()));

    ui->twCalculation->item(0, 0)->setText(QString::number(stats->totalRevenue().value(), 'f', 2) + "€");
    ui->twCalculation->item(1, 0)->setText("-" + QString::number(stats->materialExpenses().value(), 'f', 2) + "€");
    ui->twCalculation->item(2, 0)->setText("-" + QString::number(stats->factoryExpenses().value(), 'f', 2) + "€");
    ui->twCalculation->item(3, 0)->setText("-" + QString::number(stats->salesTax().value(), 'f', 2) + "€");
    ui->twCalculation->item(4, 0)->setText("+" + QString::number(stats->preTax().value(), 'f', 2) + "€");
    ui->twCalculation->item(5, 0)->setText(QString::number(stats->profit().value(), 'f', 2) + "€");

    m_plotWidget->replot();
}
