#ifndef OFFERDIALOG_H
#define OFFERDIALOG_H

#include <QFileDialog>

#include "domain/offer.h"
#include "ui/dialogs/abstractbilldialog.h"

class OfferDialog : public AbstractBillDialog
{
    Q_OBJECT
public:
    OfferDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                MaterialService::Ptr materialService, TemplateService::Ptr templateService);

signals:
    void print(Offer::Ptr);
    void save(Offer::Ptr, QString);

private slots:
    void reject() override;
    void on_btnPreview_clicked();
    void on_btnSave_clicked();

private:
    Offer::Ptr toDomainObject();
};

#endif // OFFERDIALOG_H
