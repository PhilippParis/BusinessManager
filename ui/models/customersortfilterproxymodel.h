#ifndef CUSTOMERSORTFILTERPROXYMODEL_H
#define CUSTOMERSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class CustomerSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    CustomerSortFilterProxyModel();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // CUSTOMERSORTFILTERPROXYMODEL_H
