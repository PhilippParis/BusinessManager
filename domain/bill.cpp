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







