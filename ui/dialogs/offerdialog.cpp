#include "offerdialog.h"
#include "ui_billdialog.h"

OfferDialog::OfferDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
              ProductService::Ptr productService, TemplateService::Ptr templateService) :
 AbstractBillDialog(parent, billService, customerService, productService, templateService)
{
    connect(ui->btnPreview, SIGNAL(clicked(bool)), SLOT(on_btnPreview_clicked()));
    connect(ui->btnSave, SIGNAL(clicked(bool)), SLOT(on_btnSave_clicked()));

    ui->btnAddDiscount->setHidden(true);
    ui->box_nr_date->setHidden(true);
}

void OfferDialog::reject()
{
    if (QMessageBox::warning(this, "Cancel Offer?", "Do you really want to cancel?",
                             QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
        QDialog::reject();
    }
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

void OfferDialog::on_btnSave_clicked()
{
    QFileDialog dialog(this,  tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("pdf");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("PDF Files (*.pdf)");

    if (dialog.exec()) {
        emit save(toDomainObject(), dialog.selectedFiles().first());
    }
}
