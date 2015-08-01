#include "billitemwizard.h"
#include "ui_abstractbillitemwizard.h"

BillItemWizard::BillItemWizard(QWidget *parent, BillService::Ptr billService,
                               MaterialService::Ptr materialService, TemplateService::Ptr templateService) :
    AbstractBillItemWizard(parent, materialService, templateService),
    m_billService(billService)
{
    connect(this, SIGNAL(currentIdChanged(int)), SLOT(on_BillItemWizard_currentIdChanged(int)));
}

void BillItemWizard::prepareForUpdate(BillItem::Ptr item)
{
    m_openMode = Update;

    double cost = item->materialCost() + item->workingHours() * item->wagePerHour();
    m_id = item->id();
    m_materialCost = item->materialCost();

    ui->sbPricePerUnit->setValue(item->price());
    ui->leSearchTemplate->clear();
    ui->leTemplateName->clear();
    ui->leTemplateOrg->clear();
    ui->textEditArticleDesc->setText(item->description());
    ui->leUnit->setText(item->unit());
    ui->sbQuantity->setValue(item->quantity());
    ui->sbWorkingHours->setValue(item->workingHours());
    ui->lblCostPerArticle->setText(QString::number(cost) + QString::fromUtf8("€"));
    m_materialModel->addAllWithQuantity(item->material());
}

BillItem::Ptr BillItemWizard::getBillItemDomainObject()
{
    BillItem::Ptr item = std::make_shared<BillItem>();

    QSettings settings;

    item->setId(m_id);
    item->setDescription(ui->textEditArticleDesc->toPlainText());
    item->setMaterialCost(m_materialCost);
    item->setPrice(ui->sbPricePerUnit->value());
    item->setQuantity(ui->sbQuantity->value());
    item->setUnit(ui->leUnit->text());
    item->setWorkingHours(ui->sbWorkingHours->value());
    item->setMaterial(m_materialModel->itemsWithQuantity());

    item->setWagePerHour(settings.value("financial/wage").toDouble());
    item->setMaterialOverhead(settings.value("financial/materialOverhead").toDouble());
    item->setFactoryOverhead(settings.value("financial/factoryOverhead").toDouble());
    item->setProfit(settings.value("financial/profit").toDouble());
    item->setCashback(settings.value("financial/cashback").toDouble());
    item->setTax(settings.value("financial/tax").toDouble());

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
        m_billService->billItemValidator()->validateForCreate(item);
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

void BillItemWizard::on_BillItemWizard_currentIdChanged(int id)
{
    if (id == ItemDetailsPage) {
        BillItem::Ptr item = getBillItemDomainObject();
        ui->lblCostPerArticle->setText(QString::number(item->costs(), 'f', 2) + QString::fromUtf8("€"));
        ui->sbPricePerUnit->setValue(item->price() < 0 ? 0.0 : item->price());
        ui->lblCalculatedPrice->setText(QString::number(item->calculatedPrice(), 'f', 2) + QString::fromUtf8("€"));
    }
}

