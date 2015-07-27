#ifndef PRODUCTSWIDGET_H
#define PRODUCTSWIDGET_H

#include <QWidget>

#include "service/productservice.h"

#include "ui/models/producttablemodel.h"
#include "ui/models/productsortfilterproxymodel.h"

#include "ui/dialogs/productdialog.h"

namespace Ui {
class ProductsWidget;
}

class ProductsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductsWidget(QWidget *parent = 0);
    ~ProductsWidget();

    void setProductService(ProductService::Ptr service);
    Product::Ptr selectedProduct();

private slots:
    void update();
    void on_btnAdd_clicked();

    void on_btnEdit_clicked();

    void on_btnDelete_clicked();

    void on_tblProducts_clicked(const QModelIndex &index);

private:
    Ui::ProductsWidget *ui;

    ProductService::Ptr m_service;
    ProductTableModel *m_model;
    ProductSortFilterProxyModel *m_sortFilterProxyModel;
};

#endif // PRODUCTSWIDGET_H
