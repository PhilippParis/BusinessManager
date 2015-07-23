#ifndef CUSTOMERSWIDGET_H
#define CUSTOMERSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QSqlTableModel>

#include "persistence/databasesingleton.h"

#include "ui/models/customermodel.h"
#include "ui/delegates/customeritemdelegate.h"
#include "ui/dialogs/customerdialog.h"

#include "persistence/validation/validator.h"
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

    void setValidator(Validator<Customer::Ptr>::Ptr validator);
    void setService(CustomerService::Ptr service);

private slots:
    void update();

    void on_btnAddCustomer_clicked();
    void on_btnEditCustomer_clicked();
    void on_btnSendMail_clicked();
    void on_btnDeleteCustomer_clicked();

private:
    void showErrorMessage(QString msg);

private:
    Ui::CustomersWidget *ui;

    CustomerService::Ptr m_service;
    Validator<Customer::Ptr>::Ptr m_validator;
    CustomerModel *m_model;
    QSortFilterProxyModel *m_sortFilterModel;
};

#endif // CUSTOMERSWIDGET_H
