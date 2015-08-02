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
}

Template::Ptr TemplateWizard::toDomainObject()
{
    Template::Ptr templ = toTemplate();
    templ->setId(m_id);
    return templ;
}

void TemplateWizard::on_TemplateWizard_currentIdChanged(int id)
{
    if (id == ItemDetailsPage) {
        BillItem::Ptr tmp = std::make_shared<BillItem>();
        QSettings settings;

        tmp->setMaterialCost(m_materialCost);
        tmp->setWorkingHours(ui->sbWorkingHours->value());
        tmp->setWagePerHour(Decimal::fromValue(settings.value("financial/wage").toDouble()));
        tmp->setMaterialOverhead(settings.value("financial/materialOverhead").toDouble());
        tmp->setFactoryOverhead(settings.value("financial/factoryOverhead").toDouble());
        tmp->setProfit(settings.value("financial/profit").toDouble());
        tmp->setCashback(settings.value("financial/cashback").toDouble());
        tmp->setTax(settings.value("financial/tax").toDouble());

        ui->lblCostPerArticle->setText(QString::number(tmp->costs().value(), 'f', 2) + QString::fromUtf8("€"));
        ui->sbPricePerUnit->setValue(tmp->price() < Decimal::fromValue(0.0) ? 0.0 : tmp->price().value());
        ui->lblCalculatedPrice->setText(QString::number(tmp->calculatedPrice().value(), 'f', 2) + QString::fromUtf8("€"));
    }
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



