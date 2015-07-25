#include "producttablemodel.h"

ProductTableModel::ProductTableModel()
{

}

int ProductTableModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

bool ProductTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole) {
        m_quantities.insert(m_data.at(index.row()), value.toDouble());
    }
}

QVariant ProductTableModel::data(const QModelIndex &index, int role) const
{
    Product::Ptr product = m_data.at(index.row());

    if(role == Qt::EditRole) {
        return m_quantities.value(product, 0.0);
    }

    if (role == Qt::UserRole) {
        return product->unit();
    }

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case Name:
            return product->name();
        case Nr:
            return product->articleNumber();
        case Type:
            return product->type();
        case Manufactor:
            return product->manufactor();
        case Quantity:
            return QString::number(m_quantities.value(product, 0.0)) + "  " + product->unit();
        }
    }

    return QVariant();
}

QVariant ProductTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case Name:
            return QString("Name");
        case Type:
            return QString("Type");
        case Manufactor:
            return QString("Manufactor");
        case Nr:
            return QString("Article Number");
        case Quantity:
            return QString("Quantity");
        }
    }
    return QVariant();
}

Qt::ItemFlags ProductTableModel::flags(const QModelIndex & index) const
{
    if (index.column() == 4) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    return QAbstractTableModel::flags(index);
}

void ProductTableModel::addAllWithQuantity(QMap<Product::Ptr, double> products)
{
    DomainItemModel::addAll(products.keys());
    m_quantities = products;
}

void ProductTableModel::add(Product::Ptr product, double quantity)
{
    m_quantities.insert(product, quantity);
    DomainItemModel::add(product);
}

void ProductTableModel::remove(Product::Ptr item)
{
    DomainItemModel::remove(item);
    m_quantities.remove(item);
}

void ProductTableModel::replace(Product::Ptr old, Product::Ptr updated)
{
    DomainItemModel::replace(old, updated);
    m_quantities.insert(updated, m_quantities.value(old, 0.0));
    m_quantities.remove(old);
}

void ProductTableModel::clear()
{
    DomainItemModel::clear();
    m_quantities.clear();
}

QMap<Product::Ptr, double> ProductTableModel::itemsWithQuantity() const
{
    return m_quantities;
}

