#ifndef ABSTRACTBILLDIALOG_H
#define ABSTRACTBILLDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSettings>

#include "service/billservice.h"
#include "service/customerservice.h"

#include "persistence/validation/validator.h"

#include "ui/models/customertablemodel.h"
#include "ui/models/billitemtablemodel.h"

#include "ui/dialogs/customerdialog.h"
#include "ui/dialogs/discountdialog.h"
#include "ui/wizards/billitemwizard.h"
#include "ui/dialogs/customerselectiondialog.h"
#include "ui/dialogs/templateselectiondialog.h"

namespace Ui {
class BillDialog;
}

class AbstractBillDialog : public QDialog
{
    Q_OBJECT
public:
    AbstractBillDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                       MaterialService::Ptr materialService, TemplateService::Ptr templateService);
    ~AbstractBillDialog();

    void setCustomer(Customer::Ptr customer);

signals:
    void customerAdded(Customer::Ptr);
    void templateAdded(Template::Ptr);

private slots:
    void on_btnSelectCustomer_clicked();
    void on_btnAddArticle_clicked();
    void on_btnEditArticle_clicked();
    void selectionChanged(QModelIndex newIndex, QModelIndex prevIndex);
    void on_btnDeleteArticle_clicked();

protected:
    BillItem::Ptr selectedBillItem();

protected:
    Ui::BillDialog *ui;
    Customer::Ptr m_customer;
    QDate m_date;

    BillService::Ptr m_billService;
    CustomerService::Ptr m_customerService;
    MaterialService::Ptr m_materialService;
    TemplateService::Ptr m_templateService;

    BillItemTableModel *m_billItemModel;

};

#endif // ABSTRACTBILLDIALOG_H
