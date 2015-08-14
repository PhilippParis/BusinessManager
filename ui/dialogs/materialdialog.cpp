#include "materialdialog.h"
#include "ui_materialdialog.h"

MaterialDialog::MaterialDialog(QWidget *parent, MaterialService::Ptr service) :
    QDialog(parent),
    ui(new Ui::MaterialDialog),
    m_service(service)
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
    ui->sbTax->setValue(20);
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

    ui->sbCost->setValue(material->costPerUnit().value());
    ui->sbTax->setValue(material->taxRate() * 100.0);
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

    double taxrate = (double) ui->sbTax->value() / 100.0;
    material->setCostPerUnit(Decimal::fromValue(ui->sbCost->value()));
    material->setTaxRate(taxrate);

    return material;
}

void MaterialDialog::accept()
{
    Material::Ptr material = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_service->add(material);
            emit materialAdded(material);
        } else {
            m_service->update(material);
            emit materialUpdated(material);
        }
        QDialog::accept();
    } catch (ServiceException *e) {
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
}
