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

private slots:
    void on_btnAddCustomer_clicked();
    void on_btnEditCustomer_clicked();
    void on_btnAddArticle_clicked();
    void on_btnEditArticle_clicked();
    void selectionChanged(QModelIndex newIndex, QModelIndex prevIndex);
    void on_btnDeleteArticle_clicked();

protected:
    BillItem::Ptr selectedBillItem();
    Customer::Ptr selectedCustomer();

protected:
    Ui::BillDialog *ui;

    BillService::Ptr m_billService;
    CustomerService::Ptr m_customerService;
    MaterialService::Ptr m_materialService;
    TemplateService::Ptr m_templateService;

    CustomerTableModel* m_customerModel;
    BillItemTableModel *m_billItemModel;

};

#endif // ABSTRACTBILLDIALOG_H
