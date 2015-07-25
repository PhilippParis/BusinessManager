#ifndef PRODUCTSELECTIONDIALOG_H
#define PRODUCTSELECTIONDIALOG_H

#include <QDialog>

#include "service/productservice.h"

#include "ui/models/producttablemodel.h"
#include "ui/models/productsortfilterproxymodel.h"

namespace Ui {
class ProductSelectionDialog;
}

class ProductSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductSelectionDialog(QWidget *parent, ProductService::Ptr service);
    ~ProductSelectionDialog();

    Product::Ptr selectedProduct() const;
    double quantity() const;

private slots:
    void on_tblProducts_clicked(const QModelIndex &index);

    void on_leFilter_textChanged(const QString &arg1);

private:
    Ui::ProductSelectionDialog *ui;
    ProductTableModel *m_productModel;
    ProductSortFilterProxyModel *m_sortFilterProxyModel;
    ProductService::Ptr m_service;
};

#endif // PRODUCTSELECTIONDIALOG_H
