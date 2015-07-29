#include "customertablemodel.h"

CustomerTableModel::CustomerTableModel()
 : DomainItemModel()
{

}

int CustomerTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant CustomerTableModel::data(const QModelIndex &index, int role) const
{
    Customer::Ptr customer = m_data.at(index.row());
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    switch(index.column()) {
        case Name:
            if(!customer->organisation().isEmpty()) {
                return customer->organisation() + "\n" + customer->fullName();
            }
            return customer->fullName();
        case Address:
            return customer->street() + "\n" + customer->city();
        case Mail:
            return customer->mail();
    }

    return QVariant();
}

QVariant CustomerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case Name:
                    return tr("Organisation / Name");
                case Address:
                    return tr("Address");
                case Mail:
                    return tr("Mail");
                }
            }
        }
    return QVariant();
}
