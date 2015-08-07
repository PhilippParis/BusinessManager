#include "templateswidget.h"
#include "ui_templateswidget.h"

TemplatesWidget::TemplatesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplatesWidget)
{
    ui->setupUi(this);

    m_sortFilterProxyModel = new TemplateSortFilterProxyModel();
    ui->tblTemplates->setModel(m_sortFilterProxyModel);
    ui->tblTemplates->setSortingEnabled(true);

    connect(ui->leFilter, SIGNAL(textChanged(QString)), m_sortFilterProxyModel, SLOT(setFilterWildcard(QString)));
}

TemplatesWidget::~TemplatesWidget()
{
    delete ui;
    delete m_sortFilterProxyModel;
}

void TemplatesWidget::on_btnAdd_clicked()
{
    emit create();
}

void TemplatesWidget::on_btnEdit_clicked()
{
    emit edit(selectedTemplate());
}

void TemplatesWidget::on_btnDelete_clicked()
{
    emit remove(selectedTemplate());
}

void TemplatesWidget::on_tblTemplates_clicked(const QModelIndex &index)
{
    ui->btnEdit->setEnabled(index.isValid());
    ui->btnDelete->setEnabled(index.isValid());
}

Template::Ptr TemplatesWidget::selectedTemplate()
{
    QModelIndex index = ui->tblTemplates->currentIndex();
    return m_model->get(m_sortFilterProxyModel->mapToSource(index));
}

void TemplatesWidget::setTemplateService(const TemplateService::Ptr &templateService)
{
    m_templateService = templateService;
    update();
}

void TemplatesWidget::setTemplateModel(TemplateTableModel *model)
{
    m_model = model;
    m_sortFilterProxyModel->setSourceModel(m_model);
}

void TemplatesWidget::update()
{
    m_model->addAll(m_templateService->getAll());
}

