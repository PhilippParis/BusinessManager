#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrintPreviewDialog>
#include <QDesktopServices>

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/customervalidator.h"
#include "persistence/validation/impl/billvalidator.h"
#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/materialvalidator.h"
#include "persistence/validation/impl/discountvalidator.h"
#include "persistence/validation/impl/templatevalidator.h"

#include "persistence/impl/dbcustomerdao.h"
#include "persistence/impl/dbmaterialdao.h"
#include "persistence/impl/dbbillitemdao.h"
#include "persistence/impl/dbbilldao.h"
#include "persistence/impl/dbtemplatedao.h"
#include "persistence/impl/dbdiscountdao.h"

#include "service/impl/customerserviceimpl.h"
#include "service/impl/billserviceimpl.h"
#include "service/impl/materialserviceimpl.h"
#include "service/impl/templateserviceimpl.h"
#include "service/impl/printserviceimpl.h"
#include "service/impl/statisticsserviceimpl.h"

#include "ui/dialogs/settingsdialog.h"
#include "ui/dialogs/offerdialog.h"
#include "ui/dialogs/letterdialog.h"
#include "ui/dialogs/envelopedialog.h"

#include "ui/models/billtablemodel.h"

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
    void printBill(Bill::Ptr bill);
    void printOffer(Offer::Ptr offer);
    void printLetter(Letter::Ptr letter);
    void printEnvelope(Envelope::Ptr envelope);

    void exportBill(Bill::Ptr bill);
    void exportOffer(Offer::Ptr offer, QString path);
    void exportLetter(Letter::Ptr letter, QString path);

    void createBill();
    void editBill(Bill::Ptr bill);
    void removeBill(Bill::Ptr bill);

    void openMailClient(Customer::Ptr customer);

signals:
    void dataChanged();

private slots:
    void on_actionSettings_triggered();
    void on_actionEmptyPaper_triggered();
    void on_actionImprintedPaper_triggered();
    void on_actionNewOffer_triggered();
    void on_actionNewLetter_triggered();
    void on_actionPrintEnvelope_triggered();

private:
    QString getSaveFileName();
    void initWidgets();
    void loadSettings();

private:
    Ui::MainWindow *ui;

    CustomerService::Ptr m_customerService;
    BillService::Ptr m_billService;
    MaterialService::Ptr m_materialService;
    TemplateService::Ptr m_templateService;
    PrintService::Ptr m_printService;
    StatisticsService::Ptr m_statisticsService;

    Validator<Customer::Ptr>::Ptr m_customerValidator;
    Validator<Bill::Ptr>::Ptr m_billValidator;
    Validator<BillItem::Ptr>::Ptr m_billItemValidator;
    Validator<Material::Ptr>::Ptr m_materialValidator;
    Validator<Discount::Ptr>::Ptr m_discountValidator;
    Validator<Template::Ptr>::Ptr m_templateValidator;

    BillTableModel *m_billTableModel;
};

#endif // MAINWINDOW_H
