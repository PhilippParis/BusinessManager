#ifndef CUSTOMERDIALOG_H
#define CUSTOMERDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "domain/customer.h"
#include "service/customerservice.h"

namespace Ui {
class CustomerDialog;
}

class CustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerDialog(QWidget *parent, CustomerService::Ptr customerService);
    ~CustomerDialog();

    void prepareForCreate();
    void prepareForUpdate(Customer::Ptr customer);

    Customer::Ptr toDomainObject();

private slots:
    void accept() override;

private:
    enum OpenMode {
        Create, Update
    };

    Ui::CustomerDialog *ui;
    int m_id = -1;
    CustomerService::Ptr m_customerService;
    OpenMode m_openMode;
};

#endif // CUSTOMERDIALOG_H
