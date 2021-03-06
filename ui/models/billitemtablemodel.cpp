#include "billitemtablemodel.h"

BillItemTableModel::BillItemTableModel()
{

}

int BillItemTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant BillItemTableModel::data(const QModelIndex &index, int role) const
{
    BillItem::Ptr item = m_data.at(index.row());

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch (index.column()) {
    case Desc:
        return item->description();
    case Quantity:
        return item->quantity();
    case UnitPrice:
        return QString::number(item->price().value(), 'f', 2) + QString::fromUtf8("€");
    case TotalPrice:
        return QString::number((item->price() * item->quantity()).value(), 'f', 2) + QString::fromUtf8("€");
    }

    return QVariant();
}

QVariant BillItemTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case Desc:
            return tr("Article");
        case Quantity:
            return tr("Quantity");
        case UnitPrice:
            return tr("Unit Price");
        case TotalPrice:
            return tr("Total Price");
        }
    }
    return QVariant();
}

