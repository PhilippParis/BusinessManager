#include "billwidget.h"
#include "ui_billwidget.h"

BillWidget::BillWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillWidget)
{
    ui->setupUi(this);

    m_billModel = new BillTableModel();
    m_sortFilterModel = new BillSortFilterProxyModel();
    m_sortFilterModel->setSourceModel(m_billModel);

    ui->tblData->setModel(m_sortFilterModel);
    ui->tblData->setSortingEnabled(true);
    ui->tblData->sortByColumn(1, Qt::DescendingOrder);

    ui->tblData->setColumnWidth(2, 200);
    ui->tblData->setColumnWidth(3, 200);

    connect(ui->tblData->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(selectionChanged(QModelIndex,QModelIndex)));

    connect(ui->gbFilter, SIGNAL(toggled(bool)), this, SLOT(updateFilter()));
    connect(ui->dateFrom, SIGNAL(dateChanged(QDate)), this, SLOT(updateFilter()));
    connect(ui->dateTo, SIGNAL(dateChanged(QDate)), this, SLOT(updateFilter()));
    connect(ui->cbCustomers, SIGNAL(currentIndexChanged(int)), this, SLOT(updateFilter()));
    connect(ui->cbOnlyOpen, SIGNAL(clicked(bool)), this, SLOT(updateFilter()));

    connect(m_billModel, &BillTableModel::billPayedStatusChanged, [=](Bill::Ptr bill) {
        m_billService->updateBill(bill);
    });

    m_customerModel = new CustomerTableModel();
    ui->cbCustomers->setModel(m_customerModel);
}

BillWidget::~BillWidget()
{
    delete ui;
}

void BillWidget::update()
{
    m_customerModel->clear();
    m_customerModel->addAll(m_customerService->getAll());

    m_billModel->clear();
    m_billModel->addAll(m_billService->getAllBills());

    QPair<QDate,QDate> dateRange = m_billService->billDateRange();
    ui->dateFrom->setDate(dateRange.first);
    ui->dateTo->setDate(QDate::currentDate());
}

void BillWidget::selectionChanged(QModelIndex newIndex, QModelIndex prevIndex)
{
    ui->btnDelete->setEnabled(newIndex.isValid());
    ui->btnEdit->setEnabled(newIndex.isValid());
    ui->btnExport->setEnabled(newIndex.isValid());
    ui->btnPrint->setEnabled(newIndex.isValid());
    ui->btnSendPerMail->setEnabled(newIndex.isValid() && !selectedBill()->customer()->mail().isEmpty());
}

void BillWidget::updateFilter()
{
    m_sortFilterModel->setMinDate(ui->dateFrom->date());
    m_sortFilterModel->setMaxDate(ui->dateTo->date());

    int comboBoxIndex = ui->cbCustomers->currentIndex();
    CustomerTableModel *model = (CustomerTableModel*) ui->cbCustomers->model();

    m_sortFilterModel->setCustomer(ui->gbFilter->isChecked()? model->get(model->index(comboBoxIndex, 0)) : nullptr);
    m_sortFilterModel->setOnlyOpen(ui->cbOnlyOpen->isChecked());
}

Bill::Ptr BillWidget::selectedBill()
{
    QModelIndex index = m_sortFilterModel->mapToSource(ui->tblData->currentIndex());
    return m_billModel->get(index);
}
void BillWidget::setDiscountValidator(const Validator<Discount::Ptr>::Ptr &discountValidator)
{
    m_discountValidator = discountValidator;
}

void BillWidget::actionNewBill()
{
    BillDialog *dialog = new BillDialog(this, m_billService, m_customerService, m_materialService, m_templateService);
    connect(dialog, SIGNAL(print(Bill::Ptr)), this, SIGNAL(print(Bill::Ptr)));

    dialog->setDiscountValidator(m_discountValidator);
    dialog->prepareForCreate();

    if(dialog->exec() == QDialog::Accepted) {
        Bill::Ptr bill = dialog->toDomainObject();
        try {
            m_billService->addBill(bill);
            m_billModel->add(bill);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete dialog;
}

void BillWidget::on_btnEdit_clicked()
{
    Bill::Ptr selected = selectedBill();
    BillDialog *dialog = new BillDialog(this, m_billService, m_customerService, m_materialService, m_templateService);
    connect(dialog, SIGNAL(print(Bill::Ptr)), this, SIGNAL(print(Bill::Ptr)));

    dialog->setDiscountValidator(m_discountValidator);
    dialog->prepareForUpdate(selected);

    if(dialog->exec() == QDialog::Accepted) {
        Bill::Ptr bill = dialog->toDomainObject();
        try {
            m_billService->updateBill(bill);
            m_billModel->replace(selected, bill);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete dialog;
}

void BillWidget::setBillService(const BillService::Ptr &billService)
{
    m_billService = billService;
    update();
}

void BillWidget::setCustomerService(const CustomerService::Ptr &customerService)
{
    m_customerService = customerService;
}

void BillWidget::setMaterialService(const MaterialService::Ptr &materialService)
{
    m_materialService = materialService;
}

void BillWidget::setTemplateService(const TemplateService::Ptr &templateService)
{
    m_templateService = templateService;
}

void BillWidget::on_btnPrint_clicked()
{
    emit print(selectedBill());
}

void BillWidget::on_btnExport_clicked()
{
    QFileDialog dialog(this,  tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("pdf");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("PDF Files (*.pdf)");

    if (dialog.exec()) {
        emit save(selectedBill(), dialog.selectedFiles().first());
    }
}

void BillWidget::on_btnSendPerMail_clicked()
{
    emit sendMail(selectedBill()->customer());
}

void BillWidget::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Bill"),
                                    tr("Are you sure you want to delete the selected Bill?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Bill::Ptr selected = selectedBill();
        try {
            m_billService->removeBill(selected);
            m_billModel->remove(selected);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}
