#include "templatewizard.h"
#include "ui_abstractbillitemwizard.h"

TemplateWizard::TemplateWizard(QWidget *parent, MaterialService::Ptr materialService, TemplateService::Ptr templateService) :
    AbstractBillItemWizard(parent, materialService, templateService)
{
    connect(this, SIGNAL(currentIdChanged(int)), SLOT(on_TemplateWizard_currentIdChanged(int)));
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



