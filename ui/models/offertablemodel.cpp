#include "offertablemodel.h"

OfferTableModel::OfferTableModel()
{

}

int OfferTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant OfferTableModel::data(const QModelIndex &index, int role) const
{
    Offer::Ptr offer = m_data.at(index.row());

    if(role == Qt::DisplayRole) {
        switch (index.column()) {
        case Date:
            return offer->date();
        case Name:
            return offer->customer()->fullName();
        case Org:
            return offer->customer()->organisation();
        case Price:
            return QString::number(offer->totalPrice().value()) + QString::fromUtf8("€");
        }
    }

    return QVariant();
}

QVariant OfferTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case Name:
                    return tr("Name");
                case Org:
                    return tr("Organisation");
                case Date:
                    return tr("Date");
                case Price:
                    return tr("Price");
                }
            }
        }
    return QVariant();
}

