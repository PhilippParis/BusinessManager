#ifndef CUSTOMERMODEL_H
#define CUSTOMERMODEL_H

#include <QObject>
#include <QDebug>

#include "ui/models/domainitemmodel.h"

#include "domain/customer.h"

class CustomerTableModel : public DomainItemModel<Customer::Ptr>
{
    Q_OBJECT
public:
    CustomerTableModel();
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    enum Column {
        Name, Address, Mail
    };
};

#endif // CUSTOMERMODEL_H
