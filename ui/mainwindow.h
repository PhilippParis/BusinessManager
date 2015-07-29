#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrintPreviewDialog>

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/customervalidator.h"
#include "persistence/validation/impl/billvalidator.h"
#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/productvalidator.h"
#include "persistence/validation/impl/discountvalidator.h"
#include "persistence/validation/impl/templatevalidator.h"

#include "persistence/impl/dbcustomerdao.h"
#include "persistence/impl/dbproductdao.h"
#include "persistence/impl/dbbillitemdao.h"
#include "persistence/impl/dbbilldao.h"
#include "persistence/impl/dbtemplatedao.h"
#include "persistence/impl/dbdiscountdao.h"

#include "service/impl/customerserviceimpl.h"
#include "service/impl/billserviceimpl.h"
#include "service/impl/productserviceimpl.h"
#include "service/impl/templateserviceimpl.h"
#include "service/impl/printserviceimpl.h"

#include "ui/dialogs/settingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void print(Bill::Ptr bill);

signals:
    void dataChanged();

private slots:
    void on_actionSettings_triggered();
    void on_actionEmptyPaper_triggered();
    void on_actionImprintedPaper_triggered();

private:
    void initWidgets();
    void loadSettings();

private:
    Ui::MainWindow *ui;

    CustomerService::Ptr m_customerService;
    BillService::Ptr m_billService;
    ProductService::Ptr m_productService;
    TemplateService::Ptr m_templateService;
    PrintService::Ptr m_printService;

    Validator<Customer::Ptr>::Ptr m_customerValidator;
    Validator<Bill::Ptr>::Ptr m_billValidator;
    Validator<BillItem::Ptr>::Ptr m_billItemValidator;
    Validator<Product::Ptr>::Ptr m_productValidator;
    Validator<Discount::Ptr>::Ptr m_discountValidator;
    Validator<Template::Ptr>::Ptr m_templateValidator;

};

#endif // MAINWINDOW_H
