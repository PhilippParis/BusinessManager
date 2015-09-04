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
    connect(dialog, SIGNAL(customerAdded(Customer::Ptr)), this, SIGNAL(customerAdded(Customer::Ptr)));

    if(dialog->exec() == QDialog::Accepted) {
       setCustomer(dialog->selectedCustomer());
    }

    delete dialog;
}

void AbstractBillDialog::on_btnAddArticle_clicked()
{
    Template::Ptr templ = nullptr;
    TemplateSelectionDialog *dialog = new TemplateSelectionDialog(this, m_templateService);
    if (dialog->exec() == QDialog::Accepted) {
        templ = dialog->selectedTemplate();
    }


    BillItemWizard *wizard = new BillItemWizard(this, m_billService, m_materialService, m_templateService);
    connect(wizard, SIGNAL(templateAdded(Template::Ptr)), this, SIGNAL(templateAdded(Template::Ptr)));
    connect(wizard, SIGNAL(materialAdded(Material::Ptr)), this, SIGNAL(materialAdded(Material::Ptr)));
    connect(wizard, &BillItemWizard::itemAdded, m_billItemModel, &BillItemTableModel::add);
    wizard->prepareForCreate(templ);
    wizard->exec();

    delete wizard;
}

void AbstractBillDialog::on_btnEditArticle_clicked()
{
    BillItem::Ptr selected = selectedBillItem();

    if (selected == nullptr) {
        return;
    }

    BillItemWizard *wizard = new BillItemWizard(this, m_billService, m_materialService, m_templateService);
    connect(wizard, &BillItemWizard::itemUpdated, m_billItemModel, &BillItemTableModel::update);
    wizard->prepareForUpdate(selected);
    wizard->exec();

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



