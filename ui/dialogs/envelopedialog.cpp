#include "envelopedialog.h"
#include "ui_envelopedialog.h"

EnvelopeDialog::EnvelopeDialog(QWidget *parent, CustomerService::Ptr customerService) :
    QDialog(parent),
    ui(new Ui::EnvelopeDialog),
    m_customerService(customerService)
{
    ui->setupUi(this);

    m_customerModel = new CustomerTableModel();
    m_customerModel->addAll(m_customerService->getAll());
    ui->cbCustomers->setModel(m_customerModel);

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

void EnvelopeDialog::on_btnPrint_clicked()
{
    emit print(toDomainObject());
}

Envelope::Ptr EnvelopeDialog::toDomainObject()
{
    Envelope::Ptr envelope = std::make_shared<Envelope>();

    QStringList address;
    if(ui->cb_printOrg->isChecked() && !ui->leOrg->text().isEmpty()) {
        address << ui->leOrg->text();
    }
    address << ui->leName->text();
    address << ui->leStreet->text();
    address << ui->leCity->text();

    envelope->setPageSize(ui->cbFormat->currentData().toInt());
    envelope->setOrientation(ui->cbOrientation->currentData().toInt());
    envelope->setWithWindow(ui->cbWithWindow->isChecked());
    envelope->setReceiverInfo(address);

    return envelope;
}

void EnvelopeDialog::on_cbCustomers_currentIndexChanged(int index)
{
    Q_UNUSED(index)

    Customer::Ptr customer = m_customerModel->get(m_customerModel->index(ui->cbCustomers->currentIndex(), 0));
    ui->leName->setText(customer->fullName());
    ui->leOrg->setText(customer->organisation());
    ui->leStreet->setText(customer->street());
    ui->leCity->setText(customer->city());
}
