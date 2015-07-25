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
            return QString::number(bill->totalPrice(), 'f', 2) + QString::fromUtf8("€");
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
                    return QString("Nr.");
                case Date:
                    return QString("Date");
                case Org:
                    return QString("Organisation");
                case Customer:
                    return QString("Customer");
                case Value:
                    return QString("Value");
                case Payed:
                    return QString("Payed");
                }
            }
        }
    return QVariant();
}
