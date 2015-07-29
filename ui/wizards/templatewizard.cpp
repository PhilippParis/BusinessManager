#include "templatewizard.h"
#include "ui_abstractbillitemwizard.h"

TemplateWizard::TemplateWizard(QWidget *parent, ProductService::Ptr productService, TemplateService::Ptr templateService) :
    AbstractBillItemWizard(parent, productService, templateService)
{
}

void TemplateWizard::prepareForCreate()
{
    AbstractBillItemWizard::prepareForCreate();
    ui->sbQuantity->setHidden(true);
    ui->lblQuantity->setHidden(true);
    ui->gbTemplate->setChecked(true);
    ui->gbTemplate->setCheckable(false);
}

void TemplateWizard::prepareForUpdate(Template::Ptr item)
{
    prepareForCreate();

    m_openMode = Update;
    m_id = item->id();
    ui->tblTemplates->setCurrentIndex(m_templateModel->index(m_templateModel->indexOf(item), 0));
}

Template::Ptr TemplateWizard::toDomainObject()
{
    Template::Ptr templ = toTemplate();
    templ->setId(m_id);
    return templ;
}

bool TemplateWizard::onUpdate()
{
    Template::Ptr templ = toDomainObject();
    try {
        m_templateService->validator()->validateForUpdate(templ);
    } catch (ValidationException *e) {
        QMessageBox::warning(this, tr("Invalid Data"), e->what());
        delete e;
        return false;
    }
    return true;
}

bool TemplateWizard::onCreate()
{
    Template::Ptr templ = toDomainObject();
    try {
        m_templateService->validator()->validateForCreate(templ);
    } catch (ValidationException *e) {
        QMessageBox::warning(this, tr("Invalid Data"), e->what());
        delete e;
        return false;
    }
    return true;
}

