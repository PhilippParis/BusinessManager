#ifndef TEMPLATESORTFILTERPROXYMODEL_H
#define TEMPLATESORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class TemplateSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    TemplateSortFilterProxyModel();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

};
#endif // TEMPLATESORTFILTERPROXYMODEL_H
