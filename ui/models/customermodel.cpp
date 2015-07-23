#include "customermodel.h"

CustomerModel::CustomerModel()
 :QAbstractTableModel(nullptr)
{

}

int CustomerModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

int CustomerModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant CustomerModel::data(const QModelIndex &index, int role) const
{
    Customer::Ptr customer = m_data.at(index.row());

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch(index.column()) {
        case Org:
            return customer->organisation();
        case Name:
            return customer->title() + " " + customer->surname() + " " + customer->name();
        case Address:
            return customer->street() + "\n" + customer->city();
        case Mail:
            return customer->mail();
    }
}

QVariant CustomerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case Org:
                    return QString("Organisation");
                case Name:
                    return QString("Name");
                case Address:
                    return QString("Address");
                case Mail:
                    return QString("Mail");
                }
            }
        }
    return QVariant();
}

void CustomerModel::addAll(QList<Customer::Ptr> customers)
{
    beginInsertRows(QModelIndex(), 0, customers.size() - 1);
    m_data = customers;
    endInsertRows();
}

void CustomerModel::add(Customer::Ptr customer)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_data.append(customer);
    endInsertRows();
}

void CustomerModel::remove(Customer::Ptr customer)
{
    int row = m_data.indexOf(customer);
    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeOne(customer);
    endRemoveRows();
}

void CustomerModel::replace(Customer::Ptr old, Customer::Ptr updated)
{
    int row = m_data.indexOf(old);
    m_data.replace(row, updated);
    emit dataChanged(index(0, row), index(4, row));
}

Customer::Ptr CustomerModel::get(QModelIndex index)
{
    return m_data.at(index.row());
}

void CustomerModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_data.size() - 1);
    m_data.clear();
    endRemoveRows();
}

