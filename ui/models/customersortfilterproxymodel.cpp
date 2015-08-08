#include "customersortfilterproxymodel.h"

CustomerSortFilterProxyModel::CustomerSortFilterProxyModel()
{

}

bool CustomerSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex nameIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex orgIndex = sourceModel()->index(sourceRow, 1, sourceParent);

    QString name = sourceModel()->data(nameIndex).toString();
    QString org = sourceModel()->data(orgIndex).toString();

    QRegExp filter = filterRegExp();

    return name.contains(filter) || org.contains(filter);
}

