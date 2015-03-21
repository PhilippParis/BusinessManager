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
double Bill::discount() const
{
    return m_discount;
}

void Bill::setDiscount(double discount)
{
    m_discount = discount;
}
QString Bill::discountText() const
{
    return m_discountText;
}

void Bill::setDiscountText(const QString &discountText)
{
    m_discountText = discountText;
}

QList<BillItem::Ptr> Bill::billItems() const
{
    return m_items;
}

void Bill::addBillItem(const BillItem::Ptr &item)
{
    m_items.append(item);
}

void Bill::removeBillItem(const BillItem::Ptr &item)
{
    m_items.removeOne(item);
}
int Bill::id() const
{
    return m_id;
}

void Bill::setId(int id)
{
    m_id = id;
}







