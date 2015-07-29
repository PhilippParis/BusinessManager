#include "billdialog.h"
#include "ui_billdialog.h"

BillDialog::BillDialog(QWidget *parent, BillService::Ptr billService, CustomerService::Ptr customerService,
                       ProductService::Ptr productService, TemplateService::Ptr templateService) :
    QDialog(parent),
    ui(new Ui::BillDialog),
    m_billService(billService),
    m_customerService(customerService),
    m_productService(productService),
    m_templateService(templateService)
{
    ui->setupUi(this);

    m_customerModel = new CustomerTableModel();
    m_customerModel->addAll(customerService->getAll());
    ui->cbRecipient->setModel(m_customerModel);

    m_billItemModel = new BillItemTableModel();
    ui->tblBillItems->setModel(m_billItemModel);

    connect(ui->tblBillItems->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(selectionChanged(QModelIndex,QModelIndex)));

}

BillDialog::~BillDialog()
{
    delete ui;
    delete m_customerModel;
}

void BillDialog::setDiscountValidator(Validator<Discount::Ptr>::Ptr validator)
{
    m_discountValidator = validator;
}

void BillDialog::prepareForCreate()
{
    m_openMode = Create;
    m_payed = false;
    ui->dateEdit->setDate(QDate::currentDate());
    ui->sbNr->setValue(m_billService->nextBillNumber(QDate::currentDate()));
}

void BillDialog::prepareForUpdate(Bill::Ptr bill)
{
    m_openMode = Update;
    m_id = bill->id();
    m_payed = bill->payed();
    ui->dateEdit->setDate(bill->date());
    ui->sbNr->setValue(bill->billNumber());
    m_billItemModel->addAll(m_billService->getItemsOfBill(bill->id()));

    if (!bill->discounts().isEmpty()) {
        m_discount = bill->discounts().first();
    }

    int index = m_customerModel->indexOf(bill->customer());
    if(index < 0) {
        // customer deleted -> add customer to combobox
        index = m_customerModel->add(m_customerService->get(bill->customer()->id())).row();
    }
    ui->cbRecipient->setCurrentIndex(index);
}

void BillDialog::accept()
{
    Bill::Ptr bill = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_billService->billValidator()->validateForCreate(bill);
        } else {
            m_billService->billValidator()->validateForUpdate(bill);
        }
        QDialog::accept();
    } catch (ServiceException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
        delete e;
    }
}

Bill::Ptr BillDialog::toDomainObject()
{
    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setBillNumber(ui->sbNr->value());
    bill->setDate(ui->dateEdit->date());
    bill->setId(m_id);
    bill->setCustomer(m_customerModel->get(m_customerModel->index(ui->cbRecipient->currentIndex(), 0)));
    bill->setPayed(m_payed);
    bill->setItems(m_billItemModel->items());

    if(m_discount != nullptr) {
        bill->setDiscounts(QList<Discount::Ptr>() << m_discount);
    }
    return bill;
}

BillItem::Ptr BillDialog::selectedBillItem()
{
    return m_billItemModel->get(ui->tblBillItems->currentIndex());
}

void BillDialog::on_btnAddCustomer_clicked()
{
    CustomerDialog *dialog = new CustomerDialog(this, m_customerService);
    dialog->prepareForCreate();

    if(dialog->exec() == QDialog::Accepted) {
        QModelIndex index = m_customerModel->add(dialog->toDomainObject());
        ui->cbRecipient->setCurrentIndex(index.row());
    }

    delete dialog;
}

void BillDialog::on_btnEditCustomer_clicked()
{
    CustomerDialog *dialog = new CustomerDialog(this, m_customerService);
    Customer::Ptr selected = m_customerModel->get(m_customerModel->index(ui->cbRecipient->currentIndex(), 0));
    dialog->prepareForUpdate(selected);

    if(dialog->exec() == QDialog::Accepted) {
        m_customerModel->replace(selected, dialog->toDomainObject());
    }

    delete dialog;
}

void BillDialog::on_btnAddArticle_clicked()
{
    QSettings settings;
    BillItemWizard *wizard = new BillItemWizard(this, m_billService, m_productService, m_templateService);
    wizard->setWagePerHour(settings.value("financial/wage").toDouble());
    wizard->prepareForCreate();

    if(wizard->exec() == QWizard::Accepted) {
        BillItem::Ptr item = wizard->getBillItemDomainObject();
        m_billItemModel->add(item);
    }

    delete wizard;
}

void BillDialog::on_btnEditArticle_clicked()
{
    QSettings settings;
    BillItem::Ptr selected = selectedBillItem();

    if (selected == nullptr) {
        return;
    }

    BillItemWizard *wizard = new BillItemWizard(this, m_billService, m_productService, m_templateService);
    wizard->setWagePerHour(settings.value("financial/wage").toDouble());
    wizard->prepareForUpdate(selected);

    if(wizard->exec() == QWizard::Accepted) {
        m_billItemModel->replace(selected, wizard->getBillItemDomainObject());
    }

    delete wizard;
}

void BillDialog::selectionChanged(QModelIndex newIndex, QModelIndex prevIndex)
{
    Q_UNUSED(prevIndex)
    ui->btnEditArticle->setEnabled(newIndex.isValid());
    ui->btnDeleteArticle->setEnabled(newIndex.isValid());
}

void BillDialog::on_btnDeleteArticle_clicked()
{
    m_billItemModel->remove(selectedBillItem());
}

void BillDialog::on_dateEdit_dateChanged(const QDate &date)
{
    ui->sbNr->setValue(m_billService->nextBillNumber(date));
}

void BillDialog::on_btnAddDiscount_clicked()
{
    DiscountDialog *dialog = new DiscountDialog(this, m_discountValidator);
    int idBuffer = -1;

    if (m_discount == nullptr) {
        dialog->prepareForCreate();
    } else {
        idBuffer = m_discount->id();
        m_discount->setId(1);
        dialog->prepareForUpdate(m_discount);
    }

    if (dialog->exec() == QDialog::Accepted) {
        m_discount = dialog->toDomainObject();
        m_discount->setId(idBuffer);
    }
}
