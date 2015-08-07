#include "billwidget.h"
#include "ui_billwidget.h"

BillWidget::BillWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillWidget)
{
    ui->setupUi(this);

    m_sortFilterModel = new BillSortFilterProxyModel();

    ui->tblData->setModel(m_sortFilterModel);
    ui->tblData->setSortingEnabled(true);
    ui->tblData->sortByColumn(1, Qt::DescendingOrder);

    ui->tblData->setColumnWidth(2, 200);
    ui->tblData->setColumnWidth(3, 200);

    connect(ui->tblData->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(selectionChanged(QModelIndex,QModelIndex)));

    connect(ui->dateFrom, SIGNAL(dateChanged(QDate)), this, SLOT(updateFilter()));
    connect(ui->dateTo, SIGNAL(dateChanged(QDate)), this, SLOT(updateFilter()));
    connect(ui->leFilter, SIGNAL(textChanged(QString)), this, SLOT(updateFilter()));
    connect(ui->cbOnlyOpen, SIGNAL(clicked(bool)), this, SLOT(updateFilter()));
}

BillWidget::~BillWidget()
{
    delete ui;
}

void BillWidget::update()
{
    m_billModel->clear();
    m_billModel->addAll(m_billService->getAllBills());

    QPair<QDate,QDate> dateRange = m_billService->billDateRange();
    ui->dateFrom->setDate(dateRange.first);
    ui->dateTo->setDate(QDate::currentDate());
}

void BillWidget::selectionChanged(QModelIndex newIndex, QModelIndex prevIndex)
{
    ui->btnDelete->setEnabled(newIndex.isValid());
    ui->btnEdit->setEnabled(newIndex.isValid());
    ui->btnExport->setEnabled(newIndex.isValid());
    ui->btnPrint->setEnabled(newIndex.isValid());
    ui->btnSendPerMail->setEnabled(newIndex.isValid() && !selectedBill()->customer()->mail().isEmpty());
}

void BillWidget::updateFilter()
{
    m_sortFilterModel->setMinDate(ui->dateFrom->date());
    m_sortFilterModel->setMaxDate(ui->dateTo->date());
    m_sortFilterModel->setFilterWildcard(ui->leFilter->text());
    m_sortFilterModel->setOnlyOpen(ui->cbOnlyOpen->isChecked());
}

Bill::Ptr BillWidget::selectedBill()
{
    QModelIndex index = m_sortFilterModel->mapToSource(ui->tblData->currentIndex());
    return m_billModel->get(index);
}

void BillWidget::setBillModel(BillTableModel *model)
{
    m_billModel = model;
    m_sortFilterModel->setSourceModel(m_billModel);

    connect(m_billModel, &BillTableModel::billPayedStatusChanged, [=](Bill::Ptr bill) {
        m_billService->updateBill(bill);
    });
}

void BillWidget::on_btnEdit_clicked()
{
    emit edit(selectedBill());
}

void BillWidget::setBillService(const BillService::Ptr &billService)
{
    m_billService = billService;
    update();
}

void BillWidget::on_btnPrint_clicked()
{
    emit print(selectedBill());
}

void BillWidget::on_btnExport_clicked()
{
    emit saveToFile(selectedBill());
}

void BillWidget::on_btnSendPerMail_clicked()
{
    emit sendMail(selectedBill()->customer());
}

void BillWidget::on_btnDelete_clicked()
{
    emit remove(selectedBill());
}
