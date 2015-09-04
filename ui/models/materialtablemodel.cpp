#include "materialtablemodel.h"

MaterialTableModel::MaterialTableModel()
{

}

int MaterialTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 6;
}

bool MaterialTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::EditRole) {
        m_quantities.insert(m_data.at(index.row()), value.toDouble());
        emit materialChanged();
    }

    return true;
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
        case Price:
            return QString::number(material->costPerUnit().value()) + QString::fromUtf8("€");
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
        case Price:
            return tr("Price");
        case Quantity:
            return tr("Quantity");
        }
    }
    return QVariant();
}

Qt::ItemFlags MaterialTableModel::flags(const QModelIndex & index) const
{
    if (index.column() == Quantity) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    return QAbstractTableModel::flags(index);
}

void MaterialTableModel::addAllWithQuantity(QMap<Material::Ptr, double> materials)
{
    DomainItemModel::addAll(materials.keys());
    m_quantities = materials;
    emit materialChanged();
}

QModelIndex MaterialTableModel::add(Material::Ptr material, double quantity)
{
    m_quantities.insert(material, quantity);
    QModelIndex index = DomainItemModel::add(material);
    emit materialChanged();
    return index;
}

void MaterialTableModel::remove(Material::Ptr item)
{
    DomainItemModel::remove(item);
    m_quantities.remove(item);
    emit materialChanged();
}

void MaterialTableModel::replace(Material::Ptr old, Material::Ptr updated)
{
    DomainItemModel::replace(old, updated);
    m_quantities.insert(updated, m_quantities.value(old, 0.0));
    m_quantities.remove(old);
    emit materialChanged();
}

void MaterialTableModel::clear()
{
    DomainItemModel::clear();
    m_quantities.clear();
    emit materialChanged();
}

QMap<Material::Ptr, double> MaterialTableModel::itemsWithQuantity() const
{
    return m_quantities;
}

