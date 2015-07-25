#ifndef BILLSORTFILTERPROXYMODEL_H
#define BILLSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QDate>

#include <domain/customer.h>

class BillSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    BillSortFilterProxyModel(QObject *parent = 0);

    QDate minDate() const;
    void setMinDate(const QDate &minDate);

    QDate maxDate() const;
    void setMaxDate(const QDate &maxDate);

    Customer::Ptr customer() const;
    void setCustomer(const Customer::Ptr &customer);

    void setFilteringEnabled(bool enabled);

    bool onlyOpen() const;
    void setOnlyOpen(bool onlyOpen);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    bool dateInRange(const QDate &date) const;

    QDate m_minDate;
    QDate m_maxDate;
    Customer::Ptr m_customer;
    bool m_filterEnabled = true;
    bool m_onlyOpen = false;
};

#endif // BILLSORTFILTERPROXYMODEL_H
