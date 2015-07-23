#ifndef BILLITEMTABLEMODEL_H
#define BILLITEMTABLEMODEL_H

#include "ui/models/domainitemmodel.h"

#include "domain/billitem.h"

class BillItemTableModel : public DomainItemModel<BillItem::Ptr>
{
    Q_OBJECT
public:
    BillItemTableModel();
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    enum Column {
        Desc = 0, Quantity, UnitPrice, TotalPrice
    };
};

#endif // BILLITEMTABLEMODEL_H
