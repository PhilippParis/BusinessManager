#ifndef PRODUCTSORTFILTERPROXYMODEL_H
#define PRODUCTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class ProductSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    ProductSortFilterProxyModel();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

};

#endif // PRODUCTSORTFILTERPROXYMODEL_H
