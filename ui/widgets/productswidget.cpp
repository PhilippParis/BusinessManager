#include "productswidget.h"
#include "ui_productswidget.h"

ProductsWidget::ProductsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductsWidget)
{
    ui->setupUi(this);

    m_model = new ProductTableModel();
    m_sortFilterProxyModel = new ProductSortFilterProxyModel();

    m_sortFilterProxyModel->setSourceModel(m_model);
    ui->tblProducts->setModel(m_sortFilterProxyModel);
    ui->tblProducts->setSortingEnabled(true);
    ui->tblProducts->hideColumn(4);

    connect(ui->leFilter, SIGNAL(textChanged(QString)), m_sortFilterProxyModel, SLOT(setFilterWildcard(QString)));
}

ProductsWidget::~ProductsWidget()
{
    delete ui;
    delete m_model;
    delete m_sortFilterProxyModel;
}

void ProductsWidget::setProductService(ProductService::Ptr service)
{
    m_service = service;
    update();
}

Product::Ptr ProductsWidget::selectedProduct()
{
    QModelIndex index = ui->tblProducts->currentIndex();
    return m_model->get(m_sortFilterProxyModel->mapToSource(index));
}

void ProductsWidget::update()
{
    m_model->addAll(m_service->getAll());
}

void ProductsWidget::on_btnAdd_clicked()
{
    ProductDialog *dialog = new ProductDialog(this, m_service->validator());
    dialog->prepareForCreate();
    if (dialog->exec() == QDialog::Accepted) {
        Product::Ptr product = dialog->toDomainObject();
        try {
            m_service->add(product);
            m_model->add(product, 0.0);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void ProductsWidget::on_btnEdit_clicked()
{
    Product::Ptr selected = selectedProduct();
    if (selected == nullptr) {
        return;
    }

    ProductDialog *dialog = new ProductDialog(this, m_service->validator());
    dialog->prepareForUpdate(selected);
    if (dialog->exec() == QDialog::Accepted) {
        Product::Ptr product = dialog->toDomainObject();
        try {
            m_service->update(selected);
            m_model->replace(selected, product);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void ProductsWidget::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Product"),
                                    tr("Are you sure you want to delete the selected Product?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Product::Ptr selected = selectedProduct();
        try {
            m_service->remove(selected);
            m_model->remove(selected);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void ProductsWidget::on_tblProducts_clicked(const QModelIndex &index)
{
    ui->btnEdit->setEnabled(index.isValid());
    ui->btnDelete->setEnabled(index.isValid());
}
