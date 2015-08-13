#include "customerselectiondialog.h"
#include "ui_customerselectiondialog.h"

CustomerSelectionDialog::CustomerSelectionDialog(QWidget *parent, CustomerService::Ptr service) :
    QDialog(parent),
    ui(new Ui::CustomerSelectionDialog),
    m_service(service)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    m_model = new CustomerTableModel();
    m_model->addAll(service->getAll());

    m_sortFilterProxyModel = new CustomerSortFilterProxyModel();
    m_sortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_sortFilterProxyModel->setSourceModel(m_model);

    ui->tblCustomers->setModel(m_sortFilterProxyModel);
    ui->tblCustomers->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

CustomerSelectionDialog::~CustomerSelectionDialog()
{
    delete ui;
    delete m_model;
}

Customer::Ptr CustomerSelectionDialog::selectedCustomer()
{
    QModelIndex index = ui->tblCustomers->currentIndex();
    return m_model->get(m_sortFilterProxyModel->mapToSource(index));
}

void CustomerSelectionDialog::on_tblCustomers_clicked(const QModelIndex &index)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(index.isValid());
}

void CustomerSelectionDialog::on_leFilter_textChanged(const QString &arg1)
{
    m_sortFilterProxyModel->setFilterWildcard(arg1);
}

void CustomerSelectionDialog::on_btnAddCustomer_clicked()
{
    CustomerDialog *dialog = new CustomerDialog(this, m_service);

    connect(dialog, &CustomerDialog::customerAdded, [=](Customer::Ptr customer) {
        QModelIndex index = m_model->add(customer);
        ui->tblCustomers->setCurrentIndex(m_sortFilterProxyModel->mapFromSource(index));
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        emit customerAdded(customer);
    });

    dialog->prepareForCreate();
    dialog->exec();

    delete dialog;
}
