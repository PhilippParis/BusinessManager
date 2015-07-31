#include "materialtablemodel.h"

MaterialTableModel::MaterialTableModel()
{

}

int MaterialTableModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

bool MaterialTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole) {
        m_quantities.insert(m_data.at(index.row()), value.toDouble());
    }
}

QVariant MaterialTableModel::data(const QModelIndex &index, int role) const
{
    Material::Ptr material = m_data.at(index.row());

    if(role == Qt::EditRole) {
        return m_quantities.value(material, 0.0);
    }

    if (role == Qt::UserRole) {
        return material->unit();
    }

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case Name:
            return material->name();
        case Nr:
            return material->articleNumber();
        case Type:
            return material->type();
        case Manufactor:
            return material->manufactor();
        case Quantity:
            return QString::number(m_quantities.value(material, 0.0)) + "  " + material->unit();
        }
    }

    return QVariant();
}

QVariant MaterialTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case Name:
            return tr("Name");
        case Type:
            return tr("Type");
        case Manufactor:
            return tr("Manufactor");
        case Nr:
            return tr("Article Number");
        case Quantity:
            return tr("Quantity");
        }
    }
    return QVariant();
}

Qt::ItemFlags MaterialTableModel::flags(const QModelIndex & index) const
{
    if (index.column() == 4) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    return QAbstractTableModel::flags(index);
}

void MaterialTableModel::addAllWithQuantity(QMap<Material::Ptr, double> materials)
{
    DomainItemModel::addAll(materials.keys());
    m_quantities = materials;
}

void MaterialTableModel::add(Material::Ptr material, double quantity)
{
    m_quantities.insert(material, quantity);
    DomainItemModel::add(material);
}

void MaterialTableModel::remove(Material::Ptr item)
{
    DomainItemModel::remove(item);
    m_quantities.remove(item);
}

void MaterialTableModel::replace(Material::Ptr old, Material::Ptr updated)
{
    DomainItemModel::replace(old, updated);
    m_quantities.insert(updated, m_quantities.value(old, 0.0));
    m_quantities.remove(old);
}

void MaterialTableModel::clear()
{
    DomainItemModel::clear();
    m_quantities.clear();
}

QMap<Material::Ptr, double> MaterialTableModel::itemsWithQuantity() const
{
    return m_quantities;
}

