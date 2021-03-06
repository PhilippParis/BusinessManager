#include "billwidget.h"
#include "ui_billwidget.h"

BillWidget::BillWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillWidget)
{
    ui->setupUi(this);

    m_sortFilterModel = new BillSortFilterProxyModel();
    m_sortFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tblData->setModel(m_sortFilterModel);
    ui->tblData->setSortingEnabled(true);
    ui->tblData->sortByColumn(1, Qt::DescendingOrder);
    ui->tblData->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->tblData->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(selectionChanged(QModelIndex,QModelIndex)));

    connect(ui->dateFrom, SIGNAL(dateChanged(QDate)), this, SLOT(updateFilter()));
    connect(ui->dateTo, SIGNAL(dateChanged(QDate)), this, SLOT(updateFilter()));
    connect(ui->leFilter, SIGNAL(textChanged(QString)), this, SLOT(updateFilter()));
    connect(ui->cbOnlyOpen, SIGNAL(clicked(bool)), this, SLOT(updateFilter()));

    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    m_printPreviewWidget = new QPrintPreviewWidget(printer, this);
    m_printPreviewWidget->setFont(QFont("Arial",18,QFont::Bold));
    m_printPreviewWidget->setMaximumWidth(700);
    m_printPreviewWidget->setZoomMode(QPrintPreviewWidget::FitToWidth);
    ui->hLayout_tbl->addWidget(m_printPreviewWidget);
    connect(ui->tblData, SIGNAL(clicked(QModelIndex)), m_printPreviewWidget, SLOT(updatePreview()));
}

BillWidget::~BillWidget()
{
    delete ui;
}

void BillWidget::setDateFilter(QDate from, QDate to)
{
    ui->dateFrom->setDate(from);
    ui->dateTo->setDate(to);
}

void BillWidget::selectionChanged(QModelIndex newIndex, QModelIndex prevIndex)
{
    Q_UNUSED(prevIndex)
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
    connect(m_billModel, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), m_printPreviewWidget, SLOT(updatePreview()));
}

void BillWidget::setPrintService(PrintService::Ptr service)
{
    connect(m_printPreviewWidget, &QPrintPreviewWidget::paintRequested, [=](QPrinter* printer) {
        Bill::Ptr bill = selectedBill();
        if (bill != nullptr) {
            service->printBill(printer, bill);
        }
    });
}

void BillWidget::on_btnEdit_clicked()
{
    emit edit(selectedBill());
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

void BillWidget::on_tblData_doubleClicked(const QModelIndex &index)
{
    emit print(selectedBill());
}
