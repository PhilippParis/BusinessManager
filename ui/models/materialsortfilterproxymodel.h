#ifndef MATERIALSORTFILTERPROXYMODEL_H
#define MATERIALSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class MaterialSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    MaterialSortFilterProxyModel();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

};

#endif // MATERIALSORTFILTERPROXYMODEL_H
