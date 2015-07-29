#include "customerswidget.h"
#include "ui_customerswidget.h"

#include <QListView>

CustomersWidget::CustomersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomersWidget)
{
    ui->setupUi(this);
    ui->tblData->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_model = new CustomerTableModel();
    m_sortFilterModel = new QSortFilterProxyModel();
    m_sortFilterModel->setSourceModel(m_model);

    connect(ui->leSearch, SIGNAL(textChanged(QString)), m_sortFilterModel, SLOT(setFilterWildcard(QString)));
    m_sortFilterModel->setFilterKeyColumn(0);
    m_sortFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tblData->setModel(m_sortFilterModel);
    ui->tblData->setSortingEnabled(true);
    ui->tblData->sortByColumn(0, Qt::AscendingOrder);

    ui->tblData->setColumnWidth(0, 300);
    ui->tblData->setColumnWidth(1, 200);

    connect(ui->tblData->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                                                  this, SLOT(selectionChanged(QModelIndex,QModelIndex)));
}

CustomersWidget::~CustomersWidget()
{
    delete ui;
    delete m_model;
    delete m_sortFilterModel;
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

void CustomersWidget::selectionChanged(QModelIndex newIndex, QModelIndex prevIndex)
{
    ui->btnEditCustomer->setEnabled(newIndex.isValid());
    ui->btnSendMail->setEnabled(newIndex.isValid());
    ui->btnDeleteCustomer->setEnabled(newIndex.isValid());
}

void CustomersWidget::on_btnAddCustomer_clicked()
{
    CustomerDialog *dialog = new CustomerDialog(this, m_service);
    dialog->prepareForCreate();

    if(dialog->exec() == QDialog::Accepted) {
        Customer::Ptr customer = dialog->toDomainObject();
        m_model->add(customer);
    }
}

void CustomersWidget::on_btnEditCustomer_clicked()
{
    Customer::Ptr selected = selectedCustomer();
    CustomerDialog *dialog = new CustomerDialog(this, m_service);
    dialog->prepareForUpdate(selected);

    if(dialog->exec() == QDialog::Accepted) {
        Customer::Ptr editedCustomer = dialog->toDomainObject();
        m_model->replace(selected, editedCustomer);
    }
}

void CustomersWidget::on_btnSendMail_clicked()
{

}

void CustomersWidget::on_btnDeleteCustomer_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Customer"),
                                    tr("Are you sure you want to delete the selected Customer?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Customer::Ptr selected = selectedCustomer();
        try {
            m_service->remove(selected);
            m_model->remove(selected);
        } catch (ServiceException *e) {
            showErrorMessage(e->what());
        }
    }
}

void CustomersWidget::showErrorMessage(QString msg)
{
    QMessageBox::information(this, tr("Error"), msg);
}

Customer::Ptr CustomersWidget::selectedCustomer()
{
    QModelIndex index = m_sortFilterModel->mapToSource(ui->tblData->currentIndex());
    return m_model->get(index);
}
