#include "abstractbilldialog.h"
#include "ui_billdialog.h"

AbstractBillDialog::AbstractBillDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                                       MaterialService::Ptr materialService, TemplateService::Ptr templateService)
 : QDialog(parent),
   ui(new Ui::BillDialog),
   m_billService(billService),
   m_customerService(customerService),
   m_materialService(materialService),
   m_templateService(templateService)
{
    ui->setupUi(this);

    m_billItemModel = new BillItemTableModel();
    ui->tblBillItems->setModel(m_billItemModel);

    connect(ui->tblBillItems->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(selectionChanged(QModelIndex,QModelIndex)));
}

AbstractBillDialog::~AbstractBillDialog()
{
    delete ui;
    delete m_billItemModel;
}

void AbstractBillDialog::setCustomer(Customer::Ptr customer)
{
    m_customer = customer;

    QString text;
    if(m_customer->organisation().isEmpty()) {
        text = m_customer->fullName();
    } else {
        text = m_customer->organisation() + "\n" + m_customer->fullName();
    }

    ui->btnSelectCustomer->setText(text);
}

BillItem::Ptr AbstractBillDialog::selectedBillItem()
{
    return m_billItemModel->get(ui->tblBillItems->currentIndex());
}

void AbstractBillDialog::on_btnSelectCustomer_clicked()
{
    CustomerSelectionDialog *dialog = new CustomerSelectionDialog(this, m_customerService);

    if(dialog->exec() == QDialog::Accepted) {
       setCustomer(dialog->selectedCustomer());
    }

    delete dialog;
}

void AbstractBillDialog::on_btnAddArticle_clicked()
{
    BillItemWizard *wizard = new BillItemWizard(this, m_billService, m_materialService, m_templateService);
    wizard->prepareForCreate();

    if(wizard->exec() == QWizard::Accepted) {
        BillItem::Ptr item = wizard->getBillItemDomainObject();
        m_billItemModel->add(item);
    }

    delete wizard;
}

void AbstractBillDialog::on_btnEditArticle_clicked()
{
    BillItem::Ptr selected = selectedBillItem();

    if (selected == nullptr) {
        return;
    }

    BillItemWizard *wizard = new BillItemWizard(this, m_billService, m_materialService, m_templateService);
    wizard->prepareForUpdate(selected);

    if(wizard->exec() == QWizard::Accepted) {
        m_billItemModel->replace(selected, wizard->getBillItemDomainObject());
    }

    delete wizard;
}

void AbstractBillDialog::selectionChanged(QModelIndex newIndex, QModelIndex prevIndex)
{
    Q_UNUSED(prevIndex)
    ui->btnEditArticle->setEnabled(newIndex.isValid());
    ui->btnDeleteArticle->setEnabled(newIndex.isValid());
}

void AbstractBillDialog::on_btnDeleteArticle_clicked()
{
    m_billItemModel->remove(selectedBillItem());
}



