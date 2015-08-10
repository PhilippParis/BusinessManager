#include "offersortfilterproxymodel.h"

OfferSortFilterProxyModel::OfferSortFilterProxyModel()
{

}

bool OfferSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex nameIndex = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex orgIndex = sourceModel()->index(sourceRow, 2, sourceParent);

    QString name = sourceModel()->data(nameIndex).toString();
    QString org = sourceModel()->data(orgIndex).toString();

    QRegExp filter = filterRegExp();
    return name.contains(filter) || org.contains(filter);
}


