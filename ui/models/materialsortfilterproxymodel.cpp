#include "materialsortfilterproxymodel.h"

MaterialSortFilterProxyModel::MaterialSortFilterProxyModel()
{

}

bool MaterialSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex nameIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex nrIndex = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex manufactorIndex = sourceModel()->index(sourceRow, 2, sourceParent);
    QModelIndex typeIndex = sourceModel()->index(sourceRow, 3, sourceParent);

    QString name = sourceModel()->data(nameIndex).toString();
    QString nr = sourceModel()->data(nrIndex).toString();
    QString manufactor = sourceModel()->data(manufactorIndex).toString();
    QString type = sourceModel()->data(typeIndex).toString();

    QRegExp filter = filterRegExp();
    return name.contains(filter) || nr.contains(filter) || manufactor.contains(filter) || type.contains(filter);
}

