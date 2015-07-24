#ifndef BILLDIALOG_H
#define BILLDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "service/billservice.h"
#include "service/customerservice.h"

#include "persistence/validation/validator.h"

#include "ui/models/customertablemodel.h"
#include "ui/models/billitemtablemodel.h"

#include "ui/dialogs/customerdialog.h"
#include "ui/wizards/billitemwizard.h"

namespace Ui {
class BillDialog;
}

class BillDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BillDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                        ProductService::Ptr productService, TemplateService::Ptr templateService);
    ~BillDialog();

    void prepareForCreate();
    void prepareForUpdate(Bill::Ptr bill);

private slots:
    void accept() override;

    void on_btnAddCustomer_clicked();
    void on_btnEditCustomer_clicked();
    void on_btnAddArticle_clicked();
    void on_btnEditArticle_clicked();
    void selectionChanged(QModelIndex newIndex, QModelIndex prevIndex);

    void on_btnDeleteArticle_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

private:
    Bill::Ptr toDomainObject();
    BillItem::Ptr selectedBillItem();

private:
    enum OpenMode {
        Create, Update
    };

    Ui::BillDialog *ui;
    int m_id = -1;
    bool m_payed = false;

    BillService::Ptr m_billService;
    CustomerService::Ptr m_customerService;
    ProductService::Ptr m_productService;
    TemplateService::Ptr m_templateService;

    CustomerTableModel* m_customerModel;
    BillItemTableModel *m_billItemModel;
    OpenMode m_openMode;

};

#endif // BILLDIALOG_H
