#include "templateswidget.h"
#include "ui_templateswidget.h"

TemplatesWidget::TemplatesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplatesWidget)
{
    ui->setupUi(this);

    m_model = new TemplateTableModel();
    m_sortFilterProxyModel = new TemplateSortFilterProxyModel();

    m_sortFilterProxyModel->setSourceModel(m_model);
    ui->tblTemplates->setModel(m_sortFilterProxyModel);
    ui->tblTemplates->setSortingEnabled(true);

    connect(ui->leFilter, SIGNAL(textChanged(QString)), m_sortFilterProxyModel, SLOT(setFilterWildcard(QString)));
}

TemplatesWidget::~TemplatesWidget()
{
    delete ui;
    delete m_model;
    delete m_sortFilterProxyModel;
}

void TemplatesWidget::on_btnAdd_clicked()
{
    TemplateWizard *wizard = new TemplateWizard(this, m_productService, m_templateService);
    wizard->prepareForCreate();

    if (wizard->exec() == QWizard::Accepted) {
        Template::Ptr templ = wizard->toDomainObject();
        try {
            m_templateService->add(templ);
            m_model->add(templ);
        } catch (ServiceException *e) {
            QMessageBox::information(this, "error", e->what());
            delete e;
        }
    }
}

void TemplatesWidget::on_btnEdit_clicked()
{
    Template::Ptr selected = selectedTemplate();
    if (selected == nullptr) {
        return;
    }

    TemplateWizard *wizard = new TemplateWizard(this, m_productService, m_templateService);
    wizard->prepareForUpdate(selected);

    if (wizard->exec() == QWizard::Accepted) {
        Template::Ptr updated = wizard->toDomainObject();
        try {
            m_templateService->update(updated);
            m_model->replace(selected, updated);
        } catch (ServiceException *e) {
            QMessageBox::information(this, "error", e->what());
            delete e;
        }
    }
}

void TemplatesWidget::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Template",
                                    "Are you sure you want to delete the selected Template?",
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Template::Ptr selected = selectedTemplate();
        try {
            m_templateService->remove(selected);
            m_model->remove(selected);
        } catch (ServiceException *e) {
            QMessageBox::information(this, "Error", e->what());
            delete e;
        }
    }
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

void TemplatesWidget::setProductService(const ProductService::Ptr &productService)
{
    m_productService = productService;
}

void TemplatesWidget::setTemplateService(const TemplateService::Ptr &templateService)
{
    m_templateService = templateService;
    update();
}

void TemplatesWidget::update()
{
    m_model->addAll(m_templateService->getAll());
}

