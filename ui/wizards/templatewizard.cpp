#include "templatewizard.h"
#include "ui_abstractbillitemwizard.h"

TemplateWizard::TemplateWizard(QWidget *parent, ProductService::Ptr productService, TemplateService::Ptr templateService) :
    AbstractBillItemWizard(parent, productService, templateService)
{
}

void TemplateWizard::prepareForCreate()
{
    AbstractBillItemWizard::prepareForCreate();
    ui->sbWage->setHidden(true);
    ui->sbQuantity->setHidden(true);
    ui->lblQuantity->setHidden(true);
    ui->lblWage->setHidden(true);

    ui->gbTemplate->setChecked(true);
    ui->gbTemplate->setCheckable(false);
}

void TemplateWizard::prepareForUpdate(Template::Ptr item)
{
    prepareForCreate();
    m_id = item->id();
    ui->tblTemplates->setCurrentIndex(m_templateModel->index(m_templateModel->indexOf(item), 0));
    m_productModel->clear();
    m_productModel->addAllWithQuantity(item->material());

    ui->sbWorkingHours->setValue(item->workingHours());
    ui->sbPricePerUnit->setValue(item->price());
    ui->textEditArticleDesc->setText(item->itemDesc());
    ui->leTemplateName->setText(item->name());
    ui->leTemplateOrg->setText(item->organisation());
    // TODO
}

Template::Ptr TemplateWizard::toDomainObject()
{
    Template::Ptr templ = std::make_shared<Template>();

    templ->setId(m_id);
    templ->setName(ui->leTemplateName->text());
    templ->setOrganisation(ui->leTemplateOrg->text());
    templ->setItemDesc(ui->textEditArticleDesc->toPlainText());
    templ->setUnit(ui->leUnit->text());
    templ->setPrice(ui->sbPricePerUnit->value());
    templ->setWorkingHours(ui->sbWorkingHours->value());
    templ->setMaterial(m_productModel->itemsWithQuantity());
    templ->setDesc("");
    templ->setType("");
    // TODO

    return templ;
}

bool TemplateWizard::onUpdate()
{
    Template::Ptr templ = toDomainObject();
    try {
        m_templateService->validator()->validateForUpdate(templ);
    } catch (ValidationException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
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
        QMessageBox::warning(this, "Invalid Data", e->what());
        delete e;
        return false;
    }
    return true;
}

