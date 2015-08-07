#ifndef CUSTOMERSWIDGET_H
#define CUSTOMERSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QSortFilterProxyModel>

#include "persistence/databasesingleton.h"

#include "ui/models/customertablemodel.h"
#include "ui/dialogs/customerdialog.h"

#include "service/customerservice.h"

namespace Ui {
class CustomersWidget;
}

class CustomersWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomersWidget(QWidget *parent = 0);
    ~CustomersWidget();

    void setService(CustomerService::Ptr service);
    void setCustomerModel(CustomerTableModel *model);

    Customer::Ptr selectedCustomer();

signals:
    void create();
    void edit(Customer::Ptr);
    void remove(Customer::Ptr);
    void sendMail(Customer::Ptr);

private slots:
    void update();
    void selectionChanged(QModelIndex,QModelIndex);

    void on_btnAddCustomer_clicked();
    void on_btnEditCustomer_clicked();
    void on_btnSendMail_clicked();
    void on_btnDeleteCustomer_clicked();

private:
    Ui::CustomersWidget *ui;
    CustomerService::Ptr m_service;

    CustomerTableModel *m_model;
    QSortFilterProxyModel *m_sortFilterModel;
};

#endif // CUSTOMERSWIDGET_H
