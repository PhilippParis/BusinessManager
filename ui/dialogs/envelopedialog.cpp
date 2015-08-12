#include "envelopedialog.h"
#include "ui_envelopedialog.h"

EnvelopeDialog::EnvelopeDialog(QWidget *parent, CustomerService::Ptr customerService) :
    QDialog(parent),
    ui(new Ui::EnvelopeDialog),
    m_customerService(customerService)
{
    ui->setupUi(this);

    ui->cbOrientation->addItem(tr("Portrait"), QPrinter::Portrait);
    ui->cbOrientation->addItem(tr("Landscape"), QPrinter::Landscape);

    ui->cbFormat->addItem(tr("Small (DLE)"), QPrinter::DLE);
    ui->cbFormat->addItem(tr("Medium (C5E)"), QPrinter::C5E);
    ui->cbFormat->addItem(tr("Document Case"), QPrinter::A4);

    ui->cbOrientation->setCurrentIndex(1);
}

EnvelopeDialog::~EnvelopeDialog()
{
    delete ui;
}

void EnvelopeDialog::setCustomer(Customer::Ptr customer)
{
    m_customer = customer;

    QString text;
    if (m_customer->organisation().isEmpty()) {
        text = m_customer->fullName();
    } else {
        text = m_customer->organisation() + "\n" + m_customer->fullName();
    }
    ui->btnRecipient->setText(text);
}

void EnvelopeDialog::on_btnPrint_clicked()
{
    emit print(toDomainObject());
}

Envelope::Ptr EnvelopeDialog::toDomainObject()
{
    Envelope::Ptr envelope = std::make_shared<Envelope>();

    QStringList address;
    if(ui->cb_printOrg->isChecked() && !m_customer->organisation().isEmpty()) {
        address << m_customer->organisation();
    }
    address << m_customer->fullName();
    address << m_customer->street();
    address << m_customer->city();

    envelope->setPageSize(ui->cbFormat->currentData().toInt());
    envelope->setOrientation(ui->cbOrientation->currentData().toInt());
    envelope->setWithWindow(ui->cbWithWindow->isChecked());
    envelope->setReceiverInfo(address);

    return envelope;
}

void EnvelopeDialog::on_btnRecipient_clicked()
{
    CustomerSelectionDialog *dialog = new CustomerSelectionDialog(this, m_customerService);
    if(dialog->exec() == QDialog::Accepted) {
        setCustomer(dialog->selectedCustomer());
    }

    delete dialog;
}
