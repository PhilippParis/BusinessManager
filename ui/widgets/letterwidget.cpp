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
