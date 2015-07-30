#ifndef ENVELOPEDIALOG_H
#define ENVELOPEDIALOG_H

#include <QDialog>
#include <QPrinter>

#include "domain/envelope.h"
#include "service/customerservice.h"
#include "ui/models/customertablemodel.h"

namespace Ui {
class EnvelopeDialog;
}

class EnvelopeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EnvelopeDialog(QWidget *parent, CustomerService::Ptr customerService);
    ~EnvelopeDialog();

signals:
    void print(Envelope::Ptr);

private slots:
    void on_btnPrint_clicked();

    void on_cbCustomers_currentIndexChanged(int index);

private:
    Envelope::Ptr toDomainObject();

private:
    Ui::EnvelopeDialog *ui;
    CustomerService::Ptr m_customerService;
    CustomerTableModel *m_customerModel;
};

#endif // ENVELOPEDIALOG_H
