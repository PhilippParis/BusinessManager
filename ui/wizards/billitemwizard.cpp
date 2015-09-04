#include "billitemwizard.h"
#include "ui_abstractbillitemwizard.h"

BillItemWizard::BillItemWizard(QWidget *parent, BillService::Ptr billService,
                               MaterialService::Ptr materialService, TemplateService::Ptr templateService) :
    AbstractBillItemWizard(parent, materialService, templateService),
    m_billService(billService)
{

}

void BillItemWizard::prepareForUpdate(BillItem::Ptr item)
{
    m_openMode = Update;

    m_id = item->id();
    m_materialCost = item->materialNetCost();
    m_materialNetCost = item->materialNetCost();

    ui->sbPricePerUnit->setValue(item->price().value());
    ui->leTemplateName->clear();
    ui->leTemplateOrg->clear();
    ui->textEditArticleDesc->setText(item->description());
    ui->leUnit->setText(item->unit());
    ui->sbQuantity->setValue(item->quantity());
    ui->sbWorkingHours->setValue(item->workingHours());
    ui->sbTaxRate->setValue(item->taxRate() * 100.0);
    m_materialModel->addAllWithQuantity(item->material());
}

bool BillItemWizard::onUpdate()
{
    BillItem::Ptr item = toBillItem();
    try {
        // items are not stored immediately -> item has no ID -> validate for create
        m_billService->billItemValidator()->validateForCreate(item);
        emit itemUpdated(item);

        if (ui->gbTemplate->isChecked()) {
            Template::Ptr templ = toTemplate();
            m_templateService->add(templ);
            emit templateAdded(templ);
        }
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

bool BillItemWizard::onCreate()
{
    BillItem::Ptr item = toBillItem();
    try {
        m_billService->billItemValidator()->validateForCreate(item);
        emit itemAdded(item);

        if (ui->gbTemplate->isChecked()) {
            Template::Ptr templ = toTemplate();
            m_templateService->add(templ);
            emit templateAdded(templ);
        }
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

