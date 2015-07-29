#include "offerdialog.h"
#include "ui_billdialog.h"

OfferDialog::OfferDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
              ProductService::Ptr productService, TemplateService::Ptr templateService) :
 AbstractBillDialog(parent, billService, customerService, productService, templateService)
{
    connect(ui->btnPreview, SIGNAL(clicked(bool)), SLOT(on_btnPreview_clicked()));

    ui->btnAddDiscount->setHidden(true);
    ui->box_nr_date->setHidden(true);
}

Offer::Ptr OfferDialog::toDomainObject()
{
    Offer::Ptr offer = std::make_shared<Offer>();

    offer->setCustomer(selectedCustomer());
    offer->setItems(m_billItemModel->items());

    return offer;
}

void OfferDialog::on_btnPreview_clicked()
{
    emit print(toDomainObject());
}
