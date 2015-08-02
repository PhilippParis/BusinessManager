#include "materialdialog.h"
#include "ui_materialdialog.h"

MaterialDialog::MaterialDialog(QWidget *parent, Validator<Material::Ptr>::Ptr validator) :
    QDialog(parent),
    ui(new Ui::MaterialDialog),
    m_validator(validator)
{
    ui->setupUi(this);
}

MaterialDialog::~MaterialDialog()
{
    delete ui;
}

void MaterialDialog::prepareForCreate()
{
    m_openMode = Create;

    ui->leName->clear();
    ui->leManufactor->clear();
    ui->leNr->clear();
    ui->leUnit->clear();
    ui->leType->clear();

    ui->sbCost->setValue(0.0);
    ui->sbTax->setValue(0.0);
}

void MaterialDialog::prepareForUpdate(Material::Ptr material)
{
    m_openMode = Update;
    m_id = material->id();

    ui->leName->setText(material->name());
    ui->leManufactor->setText(material->manufactor());
    ui->leNr->setText(material->articleNumber());
    ui->leUnit->setText(material->unit());
    ui->leType->setText(material->type());

    ui->sbCost->setValue((material->costPerUnit() + material->tax()).value());
    ui->sbTax->setValue(material->tax().value());
}

Material::Ptr MaterialDialog::toDomainObject()
{
    Material::Ptr material = std::make_shared<Material>();

    material->setId(m_id);
    material->setArticleNumber(ui->leNr->text());
    material->setName(ui->leName->text());
    material->setManufactor(ui->leManufactor->text());
    material->setUnit(ui->leUnit->text());
    material->setType(ui->leType->text());

    material->setCostPerUnit(Decimal::fromValue(ui->sbCost->value() - ui->sbTax->value()));
    material->setTax(Decimal::fromValue(ui->sbTax->value()));

    return material;
}

void MaterialDialog::accept()
{
    Material::Ptr material = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_validator->validateForCreate(material);
        } else {
            m_validator->validateForUpdate(material);
        }
        QDialog::accept();
    } catch (ValidationException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
        delete e;
    }
}

void MaterialDialog::on_leUnit_textChanged(const QString &arg1)
{
    QString suffix = " " + QString::fromUtf8("€");
    if(!arg1.isEmpty()) {
        suffix += "/" + arg1;
    }

    ui->sbCost->setSuffix(suffix);
    ui->sbTax->setSuffix(suffix);
}
