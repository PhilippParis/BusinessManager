#include "productdialog.h"
#include "ui_productdialog.h"

ProductDialog::ProductDialog(QWidget *parent, Validator<Product::Ptr>::Ptr validator) :
    QDialog(parent),
    ui(new Ui::ProductDialog),
    m_validator(validator)
{
    ui->setupUi(this);
}

ProductDialog::~ProductDialog()
{
    delete ui;
}

void ProductDialog::prepareForCreate()
{
    m_openMode = Create;

    ui->leName->clear();
    ui->leManufactor->clear();
    ui->leNr->clear();
    ui->leUnit->clear();
    ui->leType->clear();

    ui->sbCost->setValue(0.0);
    ui->sbPrice->setValue(0.0);
}

void ProductDialog::prepareForUpdate(Product::Ptr product)
{
    m_openMode = Update;
    m_id = product->id();

    ui->leName->setText(product->name());
    ui->leManufactor->setText(product->manufactor());
    ui->leNr->setText(product->articleNumber());
    ui->leUnit->setText(product->unit());
    ui->leType->setText(product->type());

    ui->sbCost->setValue(product->costPerUnit());
    ui->sbPrice->setValue(product->pricePerUnit());
}

Product::Ptr ProductDialog::toDomainObject()
{
    Product::Ptr product = std::make_shared<Product>();

    product->setId(m_id);
    product->setArticleNumber(ui->leNr->text());
    product->setName(ui->leName->text());
    product->setManufactor(ui->leManufactor->text());
    product->setUnit(ui->leUnit->text());
    product->setType(ui->leType->text());

    product->setCostPerUnit(ui->sbCost->value());
    product->setPricePerUnit(ui->sbPrice->value());

    return product;
}

void ProductDialog::accept()
{
    Product::Ptr product = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_validator->validateForCreate(product);
        } else {
            m_validator->validateForUpdate(product);
        }
        QDialog::accept();
    } catch (ValidationException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
        delete e;
    }
}

void ProductDialog::on_leUnit_textChanged(const QString &arg1)
{
    QString suffix = " " + QString::fromUtf8("€");
    if(!arg1.isEmpty()) {
        suffix += "/" + arg1;
    }

    ui->sbCost->setSuffix(suffix);
    ui->sbPrice->setSuffix(suffix);
}
