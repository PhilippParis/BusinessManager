#include "offerdialog.h"
#include "ui_billdialog.h"

OfferDialog::OfferDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
              MaterialService::Ptr materialService, TemplateService::Ptr templateService, OfferService::Ptr offerService) :
  AbstractBillDialog(parent, billService, customerService, materialService, templateService),
  m_offerService(offerService)
{
    connect(ui->btnPreview, SIGNAL(clicked(bool)), SLOT(on_btnPreview_clicked()));

    ui->btnDiscount->setHidden(true);
    ui->box_nr_date->setHidden(true);
}

void OfferDialog::prepareForCreate(Customer::Ptr customer)
{
    m_openMode = Create;
    ui->dateEdit->setDate(QDate::currentDate());
    setCustomer(customer);
}

void OfferDialog::prepareForUpdate(Offer::Ptr offer)
{
    m_openMode = Update;
    m_id = offer->id();
    ui->dateEdit->setDate(offer->date());
    m_billItemModel->addAll(offer->items());
    setCustomer(offer->customer());
}

void OfferDialog::reject()
{
    if (QMessageBox::warning(this, "Cancel Offer?", "Do you really want to cancel?",
                             QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        QDialog::reject();
    }
}

void OfferDialog::accept()
{
    Offer::Ptr offer = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_offerService->add(offer);
            emit offerAdded(offer);
        } else {
            m_offerService->update(offer);
            emit offerUpdated(offer);
        }
        QDialog::accept();
    } catch (ValidationException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
        delete e;
    }
}

Offer::Ptr OfferDialog::toDomainObject()
{
    Offer::Ptr offer = std::make_shared<Offer>();

    offer->setDate(ui->dateEdit->date());
    offer->setCustomer(m_customer);
    offer->setItems(m_billItemModel->items());
    offer->setId(m_id);

    return offer;
}

void OfferDialog::on_btnPreview_clicked()
{
    emit print(toDomainObject());
}
