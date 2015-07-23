#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/customervalidator.h"
#include "persistence/validation/impl/billvalidator.h"
#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/productvalidator.h"

#include "persistence/impl/dbcustomerdao.h"
#include "persistence/impl/dbproductdao.h"
#include "persistence/impl/dbbillitemdao.h"
#include "persistence/impl/dbbilldao.h"

#include "service/impl/customerserviceimpl.h"
#include "service/impl/billserviceimpl.h"
#include "service/impl/productserviceimpl.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    void initWidgets();

private:
    Ui::MainWindow *ui;
    CustomerService::Ptr m_customerService;
    BillService::Ptr m_billService;
    ProductService::Ptr m_productService;

    Validator<Customer::Ptr>::Ptr m_customerValidator;
    Validator<Bill::Ptr>::Ptr m_billValidator;
    Validator<BillItem::Ptr>::Ptr m_billItemValidator;
    Validator<Product::Ptr>::Ptr m_productValidator;

};

#endif // MAINWINDOW_H
