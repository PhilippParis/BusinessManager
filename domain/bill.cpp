#include "bill.h"

Bill::Bill()
{

}

Bill::~Bill()
{

}
Customer::Ptr Bill::customer() const
{
    return m_customer;
}

void Bill::setCustomer(const Customer::Ptr &customer)
{
    m_customer = customer;
}
int Bill::billNumber() const
{
    return m_billNumber;
}

void Bill::setBillNumber(int billNumber)
{
    m_billNumber = billNumber;
}
bool Bill::payed() const
{
    return m_payed;
}

void Bill::setPayed(bool payed)
{
    m_payed = payed;
}

int Bill::id() const
{
    return m_id;
}

void Bill::setId(int id)
{
    m_id = id;
}

QString Bill::toString() const
{
    return "Bill{id=" + QString::number(m_id) +
           ", number=" + QString::number(m_billNumber) +
           ", date=" + m_date.toString() +
           ", payed=" + (m_payed? "true" : "false") +
           ", customer=" + (m_customer == nullptr? "null" : m_customer->toString()) +
           "}";
}
QDate Bill::date() const
{
    return m_date;
}

void Bill::setDate(const QDate &date)
{
    m_date = date;
}

bool Bill::equals(const Bill::Ptr bill) const
{
    if (bill == nullptr) {
        return false;
    }
    if(m_billNumber != bill->m_billNumber) {
        return false;
    }
    if(m_date != bill->m_date) {
        return false;
    }
    if(m_payed != bill->m_payed) {
        return false;
    }
    if(m_id != bill->m_id) {
        return false;
    }
    if (m_items.size() != bill->m_items.size()) {
        return false;
    }
    for (int i = 0; i < m_items.size(); ++i) {
        if (!m_items.at(i)->equals(bill->m_items.at(i))) {
            return false;
        }
    }

    return m_customer == nullptr ? bill->m_customer == nullptr : m_customer->equals(bill->m_customer);
}
QList<BillItem::Ptr> Bill::items() const
{
    return m_items;
}

void Bill::setItems(const QList<BillItem::Ptr> &items)
{
    m_items = items;
}

Decimal Bill::totalPrice() const
{
    Decimal total;
    for (BillItem::Ptr item : m_items) {
        total += item->price() * item->quantity();
    }

    for (Discount::Ptr discount : m_discounts) {
        total -= discount->value();
    }

    return total;
}

Decimal Bill::netPrice() const
{
    Decimal sum;
    for (BillItem::Ptr item : m_items) {
        sum += item->netPrice() * item->quantity();
    }

    for (Discount::Ptr discount : m_discounts) {
        sum -= discount->value();
    }

    return sum;
}

QMap<double, Decimal> Bill::inTotalPriceIncludedTaxes() const
{
    QMap<double, Decimal> sumPerTaxRate;
    QMap<double, Decimal> taxes;

    // get total bill price without discounts
    Decimal total = Decimal::fromValue(0.0);
    for (BillItem::Ptr item : m_items) {
        total += item->price() * item->quantity();
    }

    // get sum of discounts
    Decimal discount = Decimal::fromValue(0.0);
    for (Discount::Ptr disc : m_discounts) {
        discount += disc->value();
    }

    // get different tax rates
    for (BillItem::Ptr item : m_items) {
        double taxRate = item->taxRate();
        sumPerTaxRate.insert(taxRate, sumPerTaxRate.value(taxRate, Decimal::fromValue(0.0)) + item->price() * item->quantity());
    }

    // calc tax value
    QMap<double, Decimal>::iterator i;
    for (i = sumPerTaxRate.begin(); i != sumPerTaxRate.end(); ++i) {
        double taxRate = i.key();
        Decimal priceSum = i.value();

        Decimal taxValue = (priceSum - (discount * (priceSum / total))) * (taxRate / (1.0 + taxRate));
        taxes.insert(taxRate, taxValue);
    }

    return taxes;
}

QList<Discount::Ptr> Bill::discounts() const
{
    return m_discounts;
}

void Bill::setDiscounts(const QList<Discount::Ptr> &discounts)
{
    m_discounts = discounts;
}










