#ifndef CUSTOMERMODEL_H
#define CUSTOMERMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include <QDebug>

#include "domain/customer.h"

class CustomerModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CustomerModel();
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void addAll(QList<Customer::Ptr> customers);
    void add(Customer::Ptr customer);
    void remove(Customer::Ptr customer);
    void replace(Customer::Ptr old, Customer::Ptr updated);
    Customer::Ptr get(QModelIndex index);

    void clear();

private:
    QList<Customer::Ptr> m_data;

    enum Column {
        Org = 0, Name, Address, Mail
    };
};

#endif // CUSTOMERMODEL_H
