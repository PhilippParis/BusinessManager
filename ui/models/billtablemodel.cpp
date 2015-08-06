#include "billtablemodel.h"

BillTableModel::BillTableModel()
{

}

bool BillTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole) {
        Bill::Ptr bill = m_data.at(index.row());
        bill->setPayed(value.toInt() == Qt::Checked);
        emit billPayedStatusChanged(bill);
    }
}

int BillTableModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

QVariant BillTableModel::data(const QModelIndex &index, int role) const
{
    Bill::Ptr bill = m_data.at(index.row());
    Customer::Ptr customer = bill->customer();

    if (role == Qt::UserRole) {
        return customer->id();
    }

    if (role == Qt::UserRole + 1) {
        return bill->payed();
    }

    if (role == Qt::CheckStateRole && index.column() == Payed) {
        return bill->payed()? Qt::Checked : Qt::Unchecked;
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch(index.column()) {
        case Nr:
            return bill->billNumber();
        case Date:
            return bill->date();
        case Org:
            return customer->organisation();
        case Customer:
            return customer->fullName();
        case Value:
            return QString::number(bill->totalPrice().value(), 'f', 2) + QString::fromUtf8("€");
    }

    return QVariant();
}

QVariant BillTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case Nr:
                    return tr("Nr.");
                case Date:
                    return tr("Date");
                case Org:
                    return tr("Organisation");
                case Customer:
                    return tr("Customer");
                case Value:
                    return tr("Value");
                case Payed:
                    return tr("Payed");
                }
            }
        }
    return QVariant();
}

Qt::ItemFlags BillTableModel::flags(const QModelIndex &index) const
{
    if (index.column() == Payed) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    return QAbstractTableModel::flags(index);
}
