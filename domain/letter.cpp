#include "letter.h"

Letter::Letter()
{

}

Letter::~Letter()
{
    delete m_textDoc;
}

Customer::Ptr Letter::customer() const
{
    return m_customer;
}

void Letter::setCustomer(Customer::Ptr customer)
{
    m_customer = customer;
}

QTextDocument *Letter::textDoc() const
{
    return m_textDoc;
}

void Letter::setTextDoc(QTextDocument *textDoc)
{
    m_textDoc = textDoc;
}



