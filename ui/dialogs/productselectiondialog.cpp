#include "productselectiondialog.h"
#include "ui_productselectiondialog.h"

ProductSelectionDialog::ProductSelectionDialog(QWidget *parent, ProductService::Ptr service) :
    QDialog(parent),
    ui(new Ui::ProductSelectionDialog),
    m_service(service)
{
    ui->setupUi(this);

    m_productModel = new ProductTableModel();
    m_sortFilterProxyModel = new ProductSortFilterProxyModel();
    m_sortFilterProxyModel->setSourceModel(m_productModel);

    ui->tblProducts->setModel(m_sortFilterProxyModel);

    // hide quantity column
    ui->tblProducts->hideColumn(4);

    m_productModel->addAll(m_service->getAll());
}

ProductSelectionDialog::~ProductSelectionDialog()
{
    delete ui;
    delete m_productModel;
    delete m_sortFilterProxyModel;
}

Product::Ptr ProductSelectionDialog::selectedProduct() const
{
    QModelIndex currentIndex = ui->tblProducts->currentIndex();
    return m_productModel->get(m_sortFilterProxyModel->mapToSource(currentIndex));
}

double ProductSelectionDialog::quantity() const
{
    return ui->sbQuantity->value();
}

void ProductSelectionDialog::on_tblProducts_clicked(const QModelIndex &index)
{
    QString unit = selectedProduct()->unit();
    ui->sbQuantity->setSuffix(" " + unit);
}

void ProductSelectionDialog::on_leFilter_textChanged(const QString &arg1)
{
    m_sortFilterProxyModel->setFilterWildcard(arg1);
}
