#include "customerswidget.h"
#include "ui_customerswidget.h"

#include <QListView>

CustomersWidget::CustomersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomersWidget)
{
    ui->setupUi(this);
    ui->tblData->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_model = new CustomerModel();
    m_sortFilterModel = new QSortFilterProxyModel();
    m_sortFilterModel->setSourceModel(m_model);

    connect(ui->leSearch, SIGNAL(textChanged(QString)), m_sortFilterModel, SLOT(setFilterWildcard(QString)));
    m_sortFilterModel->setFilterKeyColumn(1);
    m_sortFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tblData->setModel(m_sortFilterModel);
    ui->tblData->setSortingEnabled(true);
    ui->tblData->sortByColumn(0, Qt::AscendingOrder);
}

CustomersWidget::~CustomersWidget()
{
    delete ui;
}

void CustomersWidget::setValidator(Validator<Customer::Ptr>::Ptr validator)
{
    m_validator = validator;
}

void CustomersWidget::setService(CustomerService::Ptr service)
{
    m_service = service;
    update();
}

void CustomersWidget::update()
{
    m_model->clear();
    m_model->addAll(m_service->getAll());
}

void CustomersWidget::on_btnAddCustomer_clicked()
{
    CustomerDialog *dialog = new CustomerDialog(this, m_validator);
    dialog->prepareForCreate();

    if(dialog->exec() == QDialog::Accepted) {
        Customer::Ptr customer = dialog->toDomainObject();
        try {
            m_service->add(customer);
            m_model->add(customer);
        } catch (ServiceException *e) {
            showErrorMessage(e->what());
        }
    }
}

void CustomersWidget::on_btnEditCustomer_clicked()
{
    Customer::Ptr selectedCustomer = m_model->get(ui->tblData->selectionModel()->selectedIndexes().first());
    CustomerDialog *dialog = new CustomerDialog(this, m_validator);
    dialog->prepareForUpdate(selectedCustomer);

    if(dialog->exec() == QDialog::Accepted) {
        Customer::Ptr editedCustomer = dialog->toDomainObject();
        try {
            m_service->update(editedCustomer);
            m_model->replace(selectedCustomer, editedCustomer);
        } catch (ServiceException *e) {
            showErrorMessage(e->what());
        }
    }
}

void CustomersWidget::on_btnSendMail_clicked()
{

}

void CustomersWidget::on_btnDeleteCustomer_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Customer",
                                    "Are you sure you want to delete the selected Customer?",
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Customer::Ptr selectedCustomer = m_model->get(ui->tblData->selectionModel()->selectedIndexes().first());
        try {
            m_service->remove(selectedCustomer);
            m_model->remove(selectedCustomer);
        } catch (ServiceException *e) {
            showErrorMessage(e->what());
        }
    }
}

void CustomersWidget::showErrorMessage(QString msg)
{
    QMessageBox::information(this, "Error", msg);
}
