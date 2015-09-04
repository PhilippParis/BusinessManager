#include "templatewizard.h"
#include "ui_abstractbillitemwizard.h"

TemplateWizard::TemplateWizard(QWidget *parent, MaterialService::Ptr materialService, TemplateService::Ptr templateService) :
    AbstractBillItemWizard(parent, materialService, templateService)
{

}

void TemplateWizard::prepareForCreate()
{
    AbstractBillItemWizard::prepareForCreate(nullptr);
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
    displayTemplateData(item);
}

bool TemplateWizard::onUpdate()
{
    Template::Ptr templ = toTemplate();
    try {
        m_templateService->update(templ);
        emit templateUpdated(templ);
        return true;
    } catch (ValidationException *e) {
        QMessageBox::warning(this, tr("Invalid Data"), e->what());
        delete e;
    } catch (ServiceException *e) {
        QMessageBox::warning(this, tr("Error"), e->what());
        delete e;
    }
    return true;
}

bool TemplateWizard::onCreate()
{
    Template::Ptr templ = toTemplate();
    try {
        m_templateService->add(templ);
        emit templateAdded(templ);
        return true;
    } catch (ValidationException *e) {
        QMessageBox::warning(this, tr("Invalid Data"), e->what());
        delete e;
    } catch (ServiceException *e) {
        QMessageBox::warning(this, tr("Error"), e->what());
        delete e;
    }

    return false;
}



