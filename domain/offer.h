#ifndef OFFER_H
#define OFFER_H

#include <memory.h>
#include <QDate>

#include "domain/customer.h"
#include "domain/billitem.h"

class Offer
{
public:
    typedef std::shared_ptr<Offer> Ptr;
    Offer();

    Customer::Ptr customer() const;
    void setCustomer(const Customer::Ptr &customer);

    QList<BillItem::Ptr> items() const;
    void setItems(const QList<BillItem::Ptr> &items);

    Decimal totalPrice() const;
    Decimal netPrice() const;

    QMap<double, Decimal> inTotalPriceIncludedTaxes() const;

    QDate date() const;
    void setDate(const QDate &date);

    int id() const;
    void setId(int id);

    QString toString();

private:
    int m_id;
    Customer::Ptr m_customer;
    QList<BillItem::Ptr> m_items;
    QDate m_date;
};
Q_DECLARE_METATYPE(Offer::Ptr)

#endif // OFFER_H
