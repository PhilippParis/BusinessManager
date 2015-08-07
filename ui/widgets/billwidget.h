#ifndef BILLWIDGET_H
#define BILLWIDGET_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include <QCheckBox>
#include <QMessageBox>
#include <QFileDialog>

#include "service/billservice.h"
#include "service/customerservice.h"
#include "service/materialservice.h"
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

    void setBillService(const BillService::Ptr &billService);
    void setBillModel(BillTableModel *model);

signals:
    void print(Bill::Ptr bill);
    void edit(Bill::Ptr bill);
    void remove(Bill::Ptr bill);
    void saveToFile(Bill::Ptr bill);
    void sendMail(Customer::Ptr);

public slots:
    void update();

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

    BillTableModel *m_billModel;
    BillSortFilterProxyModel *m_sortFilterModel;
};

#endif // BILLWIDGET_H
