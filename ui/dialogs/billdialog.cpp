#include "billdialog.h"
#include "ui_billdialog.h"

BillDialog::BillDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                       MaterialService::Ptr materialService, TemplateService::Ptr templateService) :
    AbstractBillDialog(parent, billService, customerService, materialService, templateService)
{
    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), SLOT(on_dateEdit_dateChanged(QDate)));
    connect(ui->btnAddDiscount, SIGNAL(clicked(bool)), SLOT(on_btnAddDiscount_clicked()));
    connect(ui->btnPreview, SIGNAL(clicked(bool)), SLOT(on_btnPreview_clicked()));

    ui->btnSave->setHidden(true);
}

void BillDialog::setDiscountValidator(Validator<Discount::Ptr>::Ptr validator)
{
    m_discountValidator = validator;
}

void BillDialog::prepareForCreate(Customer::Ptr customer)
{
    m_openMode = Create;
    m_payed = false;
    ui->dateEdit->setDate(QDate::currentDate());
    ui->sbNr->setValue(m_billService->nextBillNumber(QDate::currentDate()));
    setCustomer(customer);
}

void BillDialog::prepareForUpdate(Bill::Ptr bill)
{
    m_openMode = Update;
    m_id = bill->id();
    m_payed = bill->payed();
    ui->dateEdit->setDate(bill->date());
    ui->sbNr->setValue(bill->billNumber());
    m_billItemModel->addAll(bill->items());
    setCustomer(bill->customer());

    if (!bill->discounts().isEmpty()) {
        m_discount = bill->discounts().first();
    }
}

void BillDialog::accept()
{
    Bill::Ptr bill = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_billService->billValidator()->validateForCreate(bill);
        } else {
            m_billService->billValidator()->validateForUpdate(bill);
        }
        QDialog::accept();
    } catch (ServiceException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
        delete e;
    }
}

Bill::Ptr BillDialog::toDomainObject()
{
    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setBillNumber(ui->sbNr->value());
    bill->setDate(ui->dateEdit->date());
    bill->setId(m_id);
    bill->setCustomer(m_customer);
    bill->setPayed(m_payed);
    bill->setItems(m_billItemModel->items());

    if(m_discount != nullptr) {
        bill->setDiscounts(QList<Discount::Ptr>() << m_discount);
    }
    return bill;
}

void BillDialog::reject()
{
    if (QMessageBox::warning(this, "Cancel Bill?", "Do you really want to cancel?",
                             QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        QDialog::reject();
    }
}

void BillDialog::on_btnPreview_clicked()
{
    emit print(toDomainObject());
}

void BillDialog::on_btnAddDiscount_clicked()
{
    DiscountDialog *dialog = new DiscountDialog(this, m_discountValidator);
    int idBuffer = -1;

    if (m_discount == nullptr) {
        dialog->prepareForCreate();
    } else {
        idBuffer = m_discount->id();
        m_discount->setId(1);
        dialog->prepareForUpdate(m_discount);
    }

    if (dialog->exec() == QDialog::Accepted) {
        m_discount = dialog->toDomainObject();
        m_discount->setId(idBuffer);
    }
}

void BillDialog::on_dateEdit_dateChanged(const QDate &date)
{
    ui->sbNr->setValue(m_billService->nextBillNumber(date));
}
