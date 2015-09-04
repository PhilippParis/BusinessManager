#include "letterwidget.h"
#include "ui_letterwidget.h"

LetterWidget::LetterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LetterWidget)
{
    ui->setupUi(this);

    m_sortFilterProxyModel = new LetterSortFilterProxyModel();
    m_sortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    ui->tblLetters->setModel(m_sortFilterProxyModel);

    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    m_printPreviewWidget = new QPrintPreviewWidget(printer, this);
    m_printPreviewWidget->setFont(QFont("Arial",18,QFont::Bold));
    m_printPreviewWidget->setMaximumWidth(700);
    m_printPreviewWidget->setZoomMode(QPrintPreviewWidget::FitToWidth);
    ui->hLayout_tbl->addWidget(m_printPreviewWidget);
    connect(ui->tblLetters, SIGNAL(clicked(QModelIndex)), m_printPreviewWidget, SLOT(updatePreview()));
}

LetterWidget::~LetterWidget()
{
    delete ui;
    delete m_sortFilterProxyModel;
}

void LetterWidget::setLetterModel(LetterTableModel *model)
{
    m_model = model;
    m_sortFilterProxyModel->setSourceModel(model);
    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)), m_printPreviewWidget, SLOT(updatePreview()));
}

void LetterWidget::setPrintService(PrintService::Ptr service)
{
    connect(m_printPreviewWidget, &QPrintPreviewWidget::paintRequested, [=](QPrinter* printer) {
        Letter::Ptr letter = selectedLetter();
        if (letter != nullptr) {
            service->printLetter(printer, letter);
        }
    });
}

void LetterWidget::on_leFilter_textChanged(const QString &arg1)
{
    m_sortFilterProxyModel->setFilterWildcard(arg1);
}

Letter::Ptr LetterWidget::selectedLetter()
{
    QModelIndex index = ui->tblLetters->currentIndex();
    return m_model->get(m_sortFilterProxyModel->mapToSource(index));
}

void LetterWidget::on_btnEdit_clicked()
{
    emit edit(selectedLetter());
}

void LetterWidget::on_btnExport_clicked()
{
    emit saveToFile(selectedLetter());
}

void LetterWidget::on_btnPrint_clicked()
{
    emit print(selectedLetter());
}

void LetterWidget::on_btnDelete_clicked()
{
    emit remove(selectedLetter());
}

void LetterWidget::on_tblLetters_clicked(const QModelIndex &index)
{
    ui->btnEdit->setEnabled(index.isValid());
    ui->btnExport->setEnabled(index.isValid());
    ui->btnPrint->setEnabled(index.isValid());
    ui->btnDelete->setEnabled(index.isValid());
}

void LetterWidget::on_tblLetters_doubleClicked(const QModelIndex &index)
{
    emit print(selectedLetter());
}
