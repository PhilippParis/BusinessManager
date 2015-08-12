#ifndef BILLDIALOG_H
#define BILLDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSettings>

#include "service/billservice.h"
#include "service/customerservice.h"

#include "persistence/validation/validator.h"

#include "ui/models/customertablemodel.h"
#include "ui/models/billitemtablemodel.h"

#include "ui/dialogs/abstractbilldialog.h"
#include "ui/dialogs/customerdialog.h"
#include "ui/dialogs/discountdialog.h"
#include "ui/wizards/billitemwizard.h"

class BillDialog : public AbstractBillDialog
{
    Q_OBJECT
public:
    explicit BillDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                        MaterialService::Ptr materialService, TemplateService::Ptr templateService);

    void setDiscountValidator(Validator<Discount::Ptr>::Ptr validator);
    void prepareForCreate(Customer::Ptr customer);
    void prepareForUpdate(Bill::Ptr bill);
    Bill::Ptr toDomainObject();

signals:
    void print(Bill::Ptr);

private slots:
    void reject() override;
    void accept() override;
    void on_btnPreview_clicked();
    void on_btnAddDiscount_clicked();
    void on_dateEdit_dateChanged(const QDate &date);

private:
    enum OpenMode {
        Create, Update
    };
    OpenMode m_openMode;

    int m_id = -1;
    bool m_payed = false;
    Discount::Ptr m_discount;
    Validator<Discount::Ptr>::Ptr m_discountValidator;

};

#endif // BILLDIALOG_H
