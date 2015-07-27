#include "templatetablemodel.h"

TemplateTableModel::TemplateTableModel()
{

}

int TemplateTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TemplateTableModel::data(const QModelIndex &index, int role) const
{
    Template::Ptr item = m_data.at(index.row());

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (index.column()) {
    case Name:
        return item->name();
    case Org:
        return item->organisation();
    case Type:
        return item->type();
    case Desc:
        return item->desc();
    }

    return QVariant();
}

QVariant TemplateTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case Name:
            return QString("Name");
        case Org:
            return QString("Organisation");
        case Type:
            return QString("Type");
        case Desc:
            return QString("Additional Description");
        }
    }
    return QVariant();
}
