#include "billtablemodel.h"

BillTableModel::BillTableModel()
{

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
        case Payed:
            return bill->payed();
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
