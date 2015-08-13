#ifndef BILLTABLEMODEL_H
#define BILLTABLEMODEL_H

#include <QDebug>
#include <QColor>

#include "ui/models/domainitemmodel.h"
#include <domain/bill.h>

class BillTableModel : public DomainItemModel<Bill::Ptr>
{
    Q_OBJECT
public:
    BillTableModel();
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:
    void billPayedStatusChanged(Bill::Ptr);

private:
    enum Column {
        Nr = 0, Date, Org, Customer, Value, Payed
    };
};

#endif // BILLTABLEMODEL_H
