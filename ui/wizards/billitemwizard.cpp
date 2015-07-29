#include "billitemwizard.h"
#include "ui_abstractbillitemwizard.h"

BillItemWizard::BillItemWizard(QWidget *parent, BillService::Ptr billService,
                               ProductService::Ptr productService, TemplateService::Ptr templateService) :
    AbstractBillItemWizard(parent, productService, templateService),
    m_billService(billService)
{
}

void BillItemWizard::prepareForUpdate(BillItem::Ptr item)
{
    m_openMode = Update;

    double cost = item->materialCost() + item->workingHours() * item->wagePerHour();
    m_id = item->id();

    ui->sbPricePerUnit->setValue(item->price());
    ui->leSearchTemplate->clear();
    ui->leTemplateName->clear();
    ui->leTemplateOrg->clear();
    ui->textEditArticleDesc->setText(item->description());
    ui->leUnit->setText(item->unit());
    ui->sbQuantity->setValue(item->quantity());
    ui->sbWorkingHours->setValue(item->workingHours());
    ui->lblCostPerArticle->setText(QString::number(cost) + QString::fromUtf8("€"));
    m_productModel->addAllWithQuantity(item->material());
}

BillItem::Ptr BillItemWizard::getBillItemDomainObject()
{
    BillItem::Ptr item = std::make_shared<BillItem>();

    item->setId(m_id);
    item->setDescription(ui->textEditArticleDesc->toPlainText());
    item->setMaterialCost(materialCosts());
    item->setPrice(ui->sbPricePerUnit->value());
    item->setQuantity(ui->sbQuantity->value());
    item->setUnit(ui->leUnit->text());
    item->setWorkingHours(ui->sbWorkingHours->value());
    item->setWagePerHour(m_wagePerHour);
    item->setMaterial(m_productModel->itemsWithQuantity());
    item->setWagePerHour(m_wagePerHour);

    return item;
}

Template::Ptr BillItemWizard::getTemplateDomainObject()
{
    if (ui->gbTemplate->isChecked()) {
        return toTemplate();
    }
    return nullptr;
}

bool BillItemWizard::onUpdate()
{
    BillItem::Ptr item = getBillItemDomainObject();
    try {
        if (ui->gbTemplate->isChecked()) {
            m_templateService->validator()->validateForCreate(toTemplate());
        }
        m_billService->billItemValidator()->validateForUpdate(item);
    } catch (Exception *e) {
        QMessageBox::warning(this, tr("Invalid Data"), e->what());
        delete e;
        return false;
    }
    return true;
}

bool BillItemWizard::onCreate()
{
    BillItem::Ptr item = getBillItemDomainObject();
    try {
        if (ui->gbTemplate->isChecked()) {
            m_templateService->validator()->validateForCreate(toTemplate());
        }
        m_billService->billItemValidator()->validateForCreate(item);
    } catch (Exception *e) {
        QMessageBox::warning(this, tr("Invalid Data"), e->what());
        delete e;
        return false;
    }
    return true;
}

