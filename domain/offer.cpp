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

QMap<double, Decimal> Offer::inTotalPriceIncludedTaxes() const
{
    QMap<double, Decimal> taxes;

    // get different tax rates
    for (BillItem::Ptr item : m_items) {
        double taxRate = item->taxRate();
        taxes.insert(taxRate, taxes.value(taxRate, Decimal::fromValue(0.0)) + item->price() * item->quantity());
    }

    QMap<double, Decimal>::iterator i;
    for (i = taxes.begin(); i != taxes.end(); i++) {
        taxes.insert(i.key(), i.value() * i.key());
    }

    return taxes;
}
QDate Offer::date() const
{
    return m_date;
}

void Offer::setDate(const QDate &date)
{
    m_date = date;
}
int Offer::id() const
{
    return m_id;
}

void Offer::setId(int id)
{
    m_id = id;
}

QString Offer::toString()
{
    return "Offer{id= " +QString::number(m_id) +
           "date= " + m_date.toString("dd.MM.yyyy")+
           "customer= " + (m_customer == nullptr? "null" : m_customer->toString()) +
    "}";
}

bool Offer::equals(const Offer::Ptr offer) const
{
    if (m_id != offer->m_id) {
        return false;
    }

    if (m_date != offer->m_date) {
        return false;
    }

    if (m_items.size() != offer->m_items.size()) {
        return false;
    }

    for (int i = 0; i < m_items.size(); ++i) {
        if (!m_items.at(i)->equals(offer->m_items.at(i))) {
            return false;
        }
    }

    return m_customer == nullptr ? offer->m_customer == nullptr : m_customer->equals(offer->m_customer);
}




