#ifndef OFFERDIALOG_H
#define OFFERDIALOG_H

#include <QFileDialog>

#include "domain/offer.h"
#include "ui/dialogs/abstractbilldialog.h"
#include "service/offerservice.h"

class OfferDialog : public AbstractBillDialog
{
    Q_OBJECT
public:
    OfferDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                MaterialService::Ptr materialService, TemplateService::Ptr templateService, OfferService::Ptr offerService);

    void prepareForCreate(Customer::Ptr customer);
    void prepareForUpdate(Offer::Ptr offer);
    Offer::Ptr toDomainObject();

signals:
    void print(Offer::Ptr);

private slots:
    void accept() override;
    void reject() override;
    void on_btnPreview_clicked();

private:
    enum OpenMode {
        Create, Update
    };
    OpenMode m_openMode;
    int m_id = -1;
    OfferService::Ptr m_offerService;
};

#endif // OFFERDIALOG_H
