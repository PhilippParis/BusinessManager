#include "customerdialog.h"
#include "ui_customerdialog.h"

CustomerDialog::CustomerDialog(QWidget *parent, Validator<Customer::Ptr>::Ptr validator) :
    QDialog(parent),
    ui(new Ui::CustomerDialog),
    m_validator(validator)
{
    ui->setupUi(this);
}

CustomerDialog::~CustomerDialog()
{
    delete ui;
}

void CustomerDialog::prepareForCreate()
{
    m_openMode = Create;
    ui->titleLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->surnameLineEdit->clear();
    ui->organisationLineEdit->clear();
    ui->streetLineEdit->clear();
    ui->cityLineEdit->clear();
    ui->mailLineEdit->clear();
}

void CustomerDialog::prepareForUpdate(Customer::Ptr customer)
{
    m_openMode = Update;
    m_id = customer->id();
    ui->titleLineEdit->setText(customer->title());
    ui->nameLineEdit->setText(customer->name());
    ui->surnameLineEdit->setText(customer->surname());
    ui->organisationLineEdit->setText(customer->organisation());
    ui->streetLineEdit->setText(customer->street());
    ui->cityLineEdit->setText(customer->city());
    ui->mailLineEdit->setText(customer->mail());
}

Customer::Ptr CustomerDialog::toDomainObject()
{
    Customer::Ptr customer = std::make_shared<Customer>();

    customer->setId(m_id);
    customer->setTitle(ui->titleLineEdit->text());
    customer->setName(ui->nameLineEdit->text());
    customer->setSurname(ui->surnameLineEdit->text());
    customer->setOrganisation(ui->organisationLineEdit->text());
    customer->setStreet(ui->streetLineEdit->text());
    customer->setCity(ui->cityLineEdit->text());
    customer->setMail(ui->mailLineEdit->text());

    return customer;
}

void CustomerDialog::accept()
{
    Customer::Ptr customer = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_validator->validateForCreate(customer);
        } else {
            m_validator->validateForUpdate(customer);
        }
    } catch (ValidationException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
        return;
    }

    QDialog::accept();
}
