#ifndef CUSTOMERSELECTIONDIALOG_H
#define CUSTOMERSELECTIONDIALOG_H

#include <QDialog>
#include <QPushButton>

#include <service/customerservice.h>

#include <ui/models/customertablemodel.h>
#include <ui/models/customersortfilterproxymodel.h>

#include <ui/dialogs/customerdialog.h>

namespace Ui {
class CustomerSelectionDialog;
}

class CustomerSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerSelectionDialog(QWidget *parent, CustomerService::Ptr service);
    ~CustomerSelectionDialog();

    Customer::Ptr selectedCustomer();

signals:
    void customerAdded(Customer::Ptr customer);

private slots:
    void on_tblCustomers_clicked(const QModelIndex &index);
    void on_leFilter_textChanged(const QString &arg1);
    void on_btnAddCustomer_clicked();

private:
    Ui::CustomerSelectionDialog *ui;
    CustomerService::Ptr m_service;
    CustomerTableModel *m_model;
    CustomerSortFilterProxyModel *m_sortFilterProxyModel;
};

#endif // CUSTOMERSELECTIONDIALOG_H
