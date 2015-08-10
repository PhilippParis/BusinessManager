#ifndef OFFERSORTFILTERPROXYMODEL_H
#define OFFERSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class OfferSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    OfferSortFilterProxyModel();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

};
#endif // OFFERSORTFILTERPROXYMODEL_H
