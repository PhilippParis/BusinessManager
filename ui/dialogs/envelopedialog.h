#ifndef ENVELOPEDIALOG_H
#define ENVELOPEDIALOG_H

#include <QDialog>
#include <QPrinter>

#include "domain/envelope.h"
#include "service/customerservice.h"
#include "ui/models/customertablemodel.h"
#include "ui/dialogs/customerselectiondialog.h"

namespace Ui {
class EnvelopeDialog;
}

class EnvelopeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnvelopeDialog(QWidget *parent, CustomerService::Ptr customerService);
    ~EnvelopeDialog();

    void setCustomer(Customer::Ptr customer);

signals:
    void print(Envelope::Ptr);
    void customerAdded(Customer::Ptr);

private slots:
    void on_btnPrint_clicked();
    void on_btnRecipient_clicked();

private:
    Envelope::Ptr toDomainObject();

private:
    Ui::EnvelopeDialog *ui;
    Customer::Ptr m_customer;
    CustomerService::Ptr m_customerService;
};

#endif // ENVELOPEDIALOG_H
