#ifndef OFFER_H
#define OFFER_H

#include <memory.h>

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

private:
    Customer::Ptr m_customer;
    QList<BillItem::Ptr> m_items;
};

#endif // OFFER_H
