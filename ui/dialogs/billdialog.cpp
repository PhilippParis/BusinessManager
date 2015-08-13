#include "billdialog.h"
#include "ui_billdialog.h"

BillDialog::BillDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                       MaterialService::Ptr materialService, TemplateService::Ptr templateService) :
    AbstractBillDialog(parent, billService, customerService, materialService, templateService)
{
    connect(ui->btnPreview, SIGNAL(clicked(bool)), SLOT(on_btnPreview_clicked()));
}

void BillDialog::setDiscountValidator(Validator<Discount::Ptr>::Ptr validator)
{
    m_discountValidator = validator;
}

void BillDialog::prepareForCreate(Customer::Ptr customer)
{
    m_openMode = Create;
    m_payed = false;
    m_date = QDate::currentDate();
    m_billNumber = m_billService->nextBillNumber(m_date);
    setCustomer(customer);
    connect(ui->btnDiscount, SIGNAL(clicked(bool)), SLOT(addDiscount()));
}

void BillDialog::prepareForUpdate(Bill::Ptr bill)
{
    m_openMode = Update;
    m_id = bill->id();
    m_payed = bill->payed();
    m_date = bill->date();
    m_billNumber = bill->billNumber();
    m_billItemModel->addAll(bill->items());
    setCustomer(bill->customer());

    if (!bill->discounts().isEmpty()) {
        m_discount = bill->discounts().first();
        ui->btnDiscount->setText(tr("Edit Discount"));
        ui->btnDiscount->setIcon(QIcon(":icon/edit"));
        connect(ui->btnDiscount, SIGNAL(clicked(bool)), SLOT(editDiscount()));
    } else {
        connect(ui->btnDiscount, SIGNAL(clicked(bool)), SLOT(addDiscount()));
    }
}

void BillDialog::accept()
{
    Bill::Ptr bill = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_billService->addBill(bill);
            emit billAdded(bill);
        } else {
            m_billService->updateBill(bill);
            emit billUpdated(bill);
        }
        QDialog::accept();
    } catch (ServiceException *e) {
        QMessageBox::warning(this, "Error", e->what());
        delete e;
    }
}

void BillDialog::addDiscount()
{
    DiscountDialog *dialog = new DiscountDialog(this, m_discountValidator);
    dialog->prepareForCreate();
    if (dialog->exec() == QDialog::Accepted) {
        m_discount = dialog->toDomainObject();

        ui->btnDiscount->disconnect(this);
        ui->btnDiscount->setText(tr("Edit Discount"));
        ui->btnDiscount->setIcon(QIcon(":icon/edit"));
        connect(ui->btnDiscount, SIGNAL(clicked(bool)), SLOT(editDiscount()));
    }
}

void BillDialog::editDiscount()
{
    DiscountDialog *dialog = new DiscountDialog(this, m_discountValidator);
    dialog->prepareForUpdate(m_discount);
    if (dialog->exec() == QDialog::Accepted) {
        m_discount = dialog->toDomainObject();
    }
}

Bill::Ptr BillDialog::toDomainObject()
{
    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setBillNumber(m_billNumber);
    bill->setDate(m_date);
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
    if (QMessageBox::warning(this, tr("Cancel Bill?"), tr("Do you really want to cancel?"),
                             QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        QDialog::reject();
    }
}

void BillDialog::on_btnPreview_clicked()
{
    emit print(toDomainObject());
}
