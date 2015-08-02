#include "discountdialog.h"
#include "ui_discountdialog.h"

DiscountDialog::DiscountDialog(QWidget *parent, Validator<Discount::Ptr>::Ptr validator) :
    QDialog(parent),
    ui(new Ui::DiscountDialog),
    m_validator(validator)
{
    ui->setupUi(this);
}

DiscountDialog::~DiscountDialog()
{
    delete ui;
}

void DiscountDialog::prepareForCreate()
{
    m_openMode = Create;

    ui->leText->clear();
    ui->sbValue->setValue(0);
}

void DiscountDialog::prepareForUpdate(Discount::Ptr discount)
{
    m_openMode = Update;

    m_id = discount->id();
    ui->sbValue->setValue(discount->value().value());
    ui->leText->setText(discount->text());
}

void DiscountDialog::accept()
{
    Discount::Ptr discount = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_validator->validateForCreate(discount);
        } else {
            m_validator->validateForUpdate(discount);
        }
        QDialog::accept();
    } catch (ValidationException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
        delete e;
    }
}

Discount::Ptr DiscountDialog::toDomainObject()
{
    Discount::Ptr discount = std::make_shared<Discount>();
    discount->setId(m_id);
    discount->setText(ui->leText->text());
    discount->setValue(Decimal::fromValue(ui->sbValue->value()));
    return discount;
}
