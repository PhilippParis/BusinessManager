#include "billsortfilterproxymodel.h"

BillSortFilterProxyModel::BillSortFilterProxyModel(QObject *parent)
 : QSortFilterProxyModel(parent)
{

}
QDate BillSortFilterProxyModel::minDate() const
{
    return m_minDate;
}

void BillSortFilterProxyModel::setMinDate(const QDate &minDate)
{
    m_minDate = minDate;
    invalidateFilter();
}
QDate BillSortFilterProxyModel::maxDate() const
{
    return m_maxDate;
}

void BillSortFilterProxyModel::setMaxDate(const QDate &maxDate)
{
    m_maxDate = maxDate;
    invalidateFilter();
}

bool BillSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    // check if filters enabled
    if(!m_filterEnabled) {
        return true;
    }

    QModelIndex payedIndex = sourceModel()->index(sourceRow, 5, sourceParent);
    QModelIndex dateIndex = sourceModel()->index(sourceRow, 1, sourceParent);

    bool payed = sourceModel()->data(payedIndex).toBool();
    QDate date = sourceModel()->data(dateIndex).toDate();

    int customerID = sourceModel()->data(dateIndex, Qt::UserRole).toInt();
    return (m_customer == nullptr || customerID == m_customer->id()) && dateInRange(date) && (m_onlyOpen ? !payed : true);
}

bool BillSortFilterProxyModel::dateInRange(const QDate &date) const
{
    return (!m_minDate.isValid() || date >= m_minDate)
               && (!m_maxDate.isValid() || date <= m_maxDate);
}
bool BillSortFilterProxyModel::onlyOpen() const
{
    return m_onlyOpen;
}

void BillSortFilterProxyModel::setOnlyOpen(bool onlyOpen)
{
    m_onlyOpen = onlyOpen;
    invalidateFilter();
}

Customer::Ptr BillSortFilterProxyModel::customer() const
{
    return m_customer;
}

void BillSortFilterProxyModel::setCustomer(const Customer::Ptr &customer)
{
    m_customer = customer;
    invalidateFilter();
}

void BillSortFilterProxyModel::setFilteringEnabled(bool enabled)
{
    m_filterEnabled = enabled;
    invalidateFilter();
}




