#include "offerwidget.h"
#include "ui_offerwidget.h"

OfferWidget::OfferWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OfferWidget)
{
    ui->setupUi(this);

    m_sortFilterProxyModel = new OfferSortFilterProxyModel();
    ui->tblOffers->setModel(m_sortFilterProxyModel);

    ui->tblOffers->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tblOffers->setSortingEnabled(true);
    ui->tblOffers->sortByColumn(0, Qt::DescendingOrder);

    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    m_printPreviewWidget = new QPrintPreviewWidget(printer, this);
    m_printPreviewWidget->setFont(QFont("Arial",18,QFont::Bold));
    m_printPreviewWidget->setMaximumWidth(700);
    m_printPreviewWidget->setZoomMode(QPrintPreviewWidget::FitToWidth);
    ui->hLayout_tbl->addWidget(m_printPreviewWidget);
    connect(ui->tblOffers, SIGNAL(clicked(QModelIndex)), m_printPreviewWidget, SLOT(updatePreview()));
}

OfferWidget::~OfferWidget()
{
    delete ui;
    delete m_sortFilterProxyModel;
}

void OfferWidget::setOfferModel(OfferTableModel *model)
{
    m_model = model;
    m_sortFilterProxyModel->setSourceModel(m_model);
    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), m_printPreviewWidget, SLOT(updatePreview()));
}

void OfferWidget::setPrintService(PrintService::Ptr service)
{
    connect(m_printPreviewWidget, &QPrintPreviewWidget::paintRequested, [=](QPrinter* printer) {
        Offer::Ptr offer = selectedOffer();
        if (offer != nullptr) {
            service->printOffer(printer, offer);
        }
    });
}

void OfferWidget::on_leFilter_textChanged(const QString &arg1)
{
    m_sortFilterProxyModel->setFilterWildcard(arg1);
}

void OfferWidget::on_btnEdit_clicked()
{
    emit edit(selectedOffer());
}

void OfferWidget::on_btnPrint_clicked()
{
    emit print(selectedOffer());
}

void OfferWidget::on_btnDelete_clicked()
{
    emit remove(selectedOffer());
}

void OfferWidget::on_btnExport_clicked()
{
    emit saveToFile(selectedOffer());
}

Offer::Ptr OfferWidget::selectedOffer()
{
    QModelIndex index = ui->tblOffers->currentIndex();
    return m_model->get(m_sortFilterProxyModel->mapToSource(index));
}

void OfferWidget::on_tblOffers_clicked(const QModelIndex &index)
{
    ui->btnDelete->setEnabled(index.isValid());
    ui->btnEdit->setEnabled(index.isValid());
    ui->btnPrint->setEnabled(index.isValid());
    ui->btnExport->setEnabled(index.isValid());
}

void OfferWidget::on_tblOffers_doubleClicked(const QModelIndex &index)
{
    emit print(selectedOffer());
}
