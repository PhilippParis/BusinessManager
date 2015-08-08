#include "customerswidget.h"
#include "ui_customerswidget.h"

#include <QListView>

CustomersWidget::CustomersWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomersWidget)
{
    ui->setupUi(this);
    ui->tblData->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_sortFilterModel = new CustomerSortFilterProxyModel();

    connect(ui->leSearch, SIGNAL(textChanged(QString)), m_sortFilterModel, SLOT(setFilterWildcard(QString)));
    m_sortFilterModel->setFilterKeyColumn(0);
    m_sortFilterModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tblData->setModel(m_sortFilterModel);
    ui->tblData->setSortingEnabled(true);
    ui->tblData->sortByColumn(0, Qt::AscendingOrder);

    ui->tblData->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(ui->tblData->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
                                                  this, SLOT(selectionChanged(QModelIndex,QModelIndex)));
}

CustomersWidget::~CustomersWidget()
{
    delete ui;
    delete m_sortFilterModel;
}

void CustomersWidget::setService(CustomerService::Ptr service)
{
    m_service = service;
    update();
}

void CustomersWidget::setCustomerModel(CustomerTableModel *model)
{
    m_model = model;
    m_sortFilterModel->setSourceModel(m_model);
}

void CustomersWidget::update()
{
    m_model->clear();
    m_model->addAll(m_service->getAll());
}

void CustomersWidget::selectionChanged(QModelIndex newIndex, QModelIndex prevIndex)
{
    ui->btnEditCustomer->setEnabled(newIndex.isValid());
    ui->btnSendMail->setEnabled(newIndex.isValid() && !selectedCustomer()->mail().isEmpty());
    ui->btnDeleteCustomer->setEnabled(newIndex.isValid());
}

void CustomersWidget::on_btnAddCustomer_clicked()
{
    emit create();
}

void CustomersWidget::on_btnEditCustomer_clicked()
{
    emit edit(selectedCustomer());
}

void CustomersWidget::on_btnSendMail_clicked()
{
    emit sendMail(selectedCustomer());
}

void CustomersWidget::on_btnDeleteCustomer_clicked()
{
    emit remove(selectedCustomer());
}

Customer::Ptr CustomersWidget::selectedCustomer()
{
    QModelIndex index = m_sortFilterModel->mapToSource(ui->tblData->currentIndex());
    return m_model->get(index);
}
