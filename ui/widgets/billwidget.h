#ifndef BILLWIDGET_H
#define BILLWIDGET_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include <QCheckBox>
#include <QMessageBox>
#include <QFileDialog>

#include "service/billservice.h"
#include "service/customerservice.h"
#include "service/productservice.h"
#include "service/templateservice.h"

#include "ui/models/billtablemodel.h"
#include "ui/models/customertablemodel.h"
#include "ui/models/billsortfilterproxymodel.h"
#include "ui/dialogs/billdialog.h"

namespace Ui {
class BillWidget;
}

class BillWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BillWidget(QWidget *parent = 0);
    ~BillWidget();

    void setTemplateService(const TemplateService::Ptr &templateService);
    void setProductService(const ProductService::Ptr &productService);
    void setCustomerService(const CustomerService::Ptr &customerService);
    void setBillService(const BillService::Ptr &billService);

    void setDiscountValidator(const Validator<Discount::Ptr>::Ptr &discountValidator);

signals:
    void print(Bill::Ptr bill);
    void save(Bill::Ptr bill, QString path);
    void sendMail(Customer::Ptr);

public slots:
    void update();
    void actionNewBill();

private slots:
    void on_btnEdit_clicked();
    void on_btnPrint_clicked();
    void on_btnExport_clicked();
    void on_btnSendPerMail_clicked();
    void on_btnDelete_clicked();

    void selectionChanged(QModelIndex newIndex, QModelIndex prevIndex);
    void updateFilter();

private:
    Bill::Ptr selectedBill();

private:
    Ui::BillWidget *ui;

    BillService::Ptr m_billService;
    CustomerService::Ptr m_customerService;
    ProductService::Ptr m_productService;
    TemplateService::Ptr m_templateService;

    Validator<Discount::Ptr>::Ptr m_discountValidator;

    BillTableModel *m_billModel;
    CustomerTableModel *m_customerModel;
    BillSortFilterProxyModel *m_sortFilterModel;
};

#endif // BILLWIDGET_H
