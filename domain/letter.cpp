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
int Letter::id() const
{
    return m_id;
}

void Letter::setId(int id)
{
    m_id = id;
}
QDate Letter::date() const
{
    return m_date;
}

void Letter::setDate(const QDate &date)
{
    m_date = date;
}

QString Letter::toString()
{
    return "Letter {id = " + QString::number(m_id) +
           "date = " + m_date.toString() +
           "customer = " + (m_customer == nullptr? "null" : m_customer->toString()) +
            "}";
}

bool Letter::equals(const Letter::Ptr letter) const
{
    if (m_id != letter->m_id) {
        return false;
    }
    if (m_date != letter->m_date) {
        return false;
    }
    if (m_textDoc->toHtml().compare(letter->m_textDoc->toHtml()) != 0) {
        return false;
    }

    return m_customer == nullptr ? letter->m_customer == nullptr : m_customer->equals(letter->m_customer);
}





