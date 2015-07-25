#ifndef PRODUCTTABLEMODEL_H
#define PRODUCTTABLEMODEL_H

#include "ui/models/domainitemmodel.h"

#include "domain/product.h"

class ProductTableModel : public DomainItemModel<Product::Ptr>
{
    Q_OBJECT
public:
    ProductTableModel();
    int columnCount(const QModelIndex &parent) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &) const override;

    void addAllWithQuantity(QMap<Product::Ptr, double> products);
    void add(Product::Ptr product, double quantity);

    void remove(Product::Ptr item) override;
    void replace(Product::Ptr old, Product::Ptr updated) override;
    void clear() override;

    QMap<Product::Ptr, double> itemsWithQuantity() const;

private:
    enum Column {
        Name = 0, Nr, Manufactor, Type, Quantity
    };

    QMap<Product::Ptr, double> m_quantities;
};

#endif // PRODUCTTABLEMODEL_H
