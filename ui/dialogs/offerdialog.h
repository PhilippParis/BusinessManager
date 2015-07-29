#ifndef OFFERDIALOG_H
#define OFFERDIALOG_H

#include "domain/offer.h"
#include "ui/dialogs/abstractbilldialog.h"

class OfferDialog : public AbstractBillDialog
{
    Q_OBJECT
public:
    OfferDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                ProductService::Ptr productService, TemplateService::Ptr templateService);

signals:
    void print(Offer::Ptr);

private slots:
    void on_btnPreview_clicked();

private:
    Offer::Ptr toDomainObject();
};

#endif // OFFERDIALOG_H
