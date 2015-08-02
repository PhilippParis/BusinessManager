#include "offer.h"

Offer::Offer()
{

}

Customer::Ptr Offer::customer() const
{
    return m_customer;
}

void Offer::setCustomer(const Customer::Ptr &customer)
{
    m_customer = customer;
}
QList<BillItem::Ptr> Offer::items() const
{
    return m_items;
}

void Offer::setItems(const QList<BillItem::Ptr> &items)
{
    m_items = items;
}

Decimal Offer::totalPrice() const
{
    Decimal total = Decimal::fromValue(0.0);
    for(BillItem::Ptr item : m_items) {
        total += item->price() * item->quantity();
    }
    return total;
}

Decimal Offer::netPrice() const
{
    Decimal total = Decimal::fromValue(0.0);
    for(BillItem::Ptr item : m_items) {
        total += item->netPrice() * item->quantity();
    }
    return total;
}


