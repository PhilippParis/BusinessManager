#ifndef OFFERTABLEMODEL_H
#define OFFERTABLEMODEL_H

#include "ui/models/domainitemmodel.h"
#include "domain/offer.h"

class OfferTableModel : public DomainItemModel<Offer::Ptr>
{
    Q_OBJECT
public:
    OfferTableModel();
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    enum Column {
        Date, Name, Org, Price
    };
};

#endif // OFFERTABLEMODEL_H
