#include "templateselectiondialog.h"
#include "ui_templateselectiondialog.h"

TemplateSelectionDialog::TemplateSelectionDialog(QWidget *parent, TemplateService::Ptr templateService) :
    QDialog(parent),
    ui(new Ui::TemplateSelectionDialog),
    m_templateService(templateService)
{
    ui->setupUi(this);

    m_templateModel = new TemplateTableModel();
    m_templateSortFilterProxyModel = new TemplateSortFilterProxyModel();
    m_templateSortFilterProxyModel->setSourceModel(m_templateModel);
    m_templateSortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    m_templateModel->addAll(m_templateService->getAll());

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Continue Without Template"));

    ui->tblTemplates->setModel(m_templateSortFilterProxyModel);
}

TemplateSelectionDialog::~TemplateSelectionDialog()
{
    delete ui;
    delete m_templateModel;
    delete m_templateSortFilterProxyModel;
}

Template::Ptr TemplateSelectionDialog::selectedTemplate()
{
    QModelIndex index = ui->tblTemplates->currentIndex();
    return m_templateModel->get(m_templateSortFilterProxyModel->mapToSource(index));
}

void TemplateSelectionDialog::on_leFilter_textChanged(const QString &arg1)
{
    m_templateSortFilterProxyModel->setFilterWildcard(arg1);
}

void TemplateSelectionDialog::on_tblTemplates_clicked(const QModelIndex &index)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(index.isValid());;
}
