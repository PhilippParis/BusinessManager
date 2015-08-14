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

    Decimal cost = item->materialCost() + item->wagePerHour() * item->workingHours();
    m_id = item->id();
    m_materialCost = item->materialCost();

    ui->sbPricePerUnit->setValue(item->price().value());
    ui->leSearchTemplate->clear();
    ui->leTemplateName->clear();
    ui->leTemplateOrg->clear();
    ui->textEditArticleDesc->setText(item->description());
    ui->leUnit->setText(item->unit());
    ui->sbQuantity->setValue(item->quantity());
    ui->sbWorkingHours->setValue(item->workingHours());
    ui->lblCostPerArticle->setText(QString::number(cost.value()) + QString::fromUtf8("€"));
    ui->sbTaxRate->setValue(item->taxRate() * 100.0);
    m_materialModel->addAllWithQuantity(item->material());
}

BillItem::Ptr BillItemWizard::getBillItemDomainObject()
{
    BillItem::Ptr item = std::make_shared<BillItem>();

    QSettings settings;

    item->setId(m_id);
    item->setDescription(ui->textEditArticleDesc->toPlainText());
    item->setMaterialCost(m_materialCost);
    item->setPrice(Decimal::fromValue(ui->sbPricePerUnit->value()));
    item->setQuantity(ui->sbQuantity->value());
    item->setUnit(ui->leUnit->text());
    item->setWorkingHours(ui->sbWorkingHours->value());
    item->setMaterial(m_materialModel->itemsWithQuantity());

    item->setWagePerHour(Decimal::fromValue(settings.value("financial/wage").toDouble()));
    item->setMaterialOverhead(settings.value("financial/materialOverhead").toDouble());
    item->setFactoryOverhead(settings.value("financial/factoryOverhead").toDouble());
    item->setProfit(settings.value("financial/profit").toDouble());
    item->setCashback(settings.value("financial/cashback").toDouble());
    item->setTaxRate(ui->sbTaxRate->value() / 100.0);

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
    BillItem::Ptr item = getBillItemDomainObject();
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

void BillItemWizard::on_BillItemWizard_currentIdChanged(int id)
{
    if (id == ItemDetailsPage) {
        BillItem::Ptr item = getBillItemDomainObject();
        ui->lblCostPerArticle->setText(QString::number(item->costs().value(), 'f', 2) + QString::fromUtf8("€"));
        ui->sbPricePerUnit->setValue(item->price() < Decimal::fromValue(0.0) ? 0.0 : item->price().value());
        ui->lblCalculatedPrice->setText(QString::number(item->calculatedPrice().value(), 'f', 2) + QString::fromUtf8("€"));
    }
}

