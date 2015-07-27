#include "templatesortfilterproxymodel.h"

TemplateSortFilterProxyModel::TemplateSortFilterProxyModel()
{

}

bool TemplateSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex nameIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex orgIndex = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex typeIndex = sourceModel()->index(sourceRow, 2, sourceParent);
    QModelIndex descIndex = sourceModel()->index(sourceRow, 3, sourceParent);

    QString name = sourceModel()->data(nameIndex).toString();
    QString org = sourceModel()->data(orgIndex).toString();
    QString type = sourceModel()->data(typeIndex).toString();
    QString desc = sourceModel()->data(descIndex).toString();

    QRegExp filter = filterRegExp();
    return name.contains(filter) || org.contains(filter) || desc.contains(filter) || type.contains(filter);
}
