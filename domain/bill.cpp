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







