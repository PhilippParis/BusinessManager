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

    switch(role) {
    case Qt::TextColorRole:
        return bill->date().daysTo(QDate::currentDate()) >=7 && !bill->payed()? QColor(Qt::red) : QColor(Qt::black);
        break;

    case Qt::UserRole:
        return customer->fullName() + "\n" + customer->organisation();
        break;

    case Qt::UserRole + 1:
        return bill->payed();
        break;

    case Qt::CheckStateRole:
        if (index.column() == Payed) {
            return bill->payed()? Qt::Checked : Qt::Unchecked;
        }
        break;

    case Qt::DisplayRole:
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
        break;
    };

    return QVariant();
}

QVariant BillTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
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
    return QVariant();
}

Qt::ItemFlags BillTableModel::flags(const QModelIndex &index) const
{
    if (index.column() == Payed) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }
    return QAbstractTableModel::flags(index);
}
