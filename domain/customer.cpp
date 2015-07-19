#include "customer.h"

Customer::Customer()
{

}

Customer::~Customer()
{

}

QString Customer::title() const
{
    return m_title;
}

void Customer::setTitle(const QString &title)
{
    m_title = title;
}
QString Customer::name() const
{
    return m_name;
}

void Customer::setName(const QString &name)
{
    m_name = name;
}
QString Customer::surname() const
{
    return m_surname;
}

void Customer::setSurname(const QString &surname)
{
    m_surname = surname;
}
QString Customer::organisation() const
{
    return m_organisation;
}

void Customer::setOrganisation(const QString &organisation)
{
    m_organisation = organisation;
}
QString Customer::street() const
{
    return m_street;
}

void Customer::setStreet(const QString &street)
{
    m_street = street;
}
QString Customer::city() const
{
    return m_city;
}

void Customer::setCity(const QString &city)
{
    m_city = city;
}
QString Customer::mail() const
{
    return m_mail;
}

void Customer::setMail(const QString &mail)
{
    m_mail = mail;
}
int Customer::id() const
{
    return m_id;
}

void Customer::setId(int id)
{
    m_id = id;
}

QString Customer::toString() const
{
    return "Customer{id=" + QString::number(m_id) +
           ", title=" + m_title +
           ", name=" + m_name +
           ", surname=" + m_surname +
           ", org=" + m_organisation +
           ", street=" + m_street +
           ", city=" + m_city +
           ", mail=" + m_mail +
            "}";
}

bool Customer::equals(Customer::Ptr customer) const
{
    if (m_title.compare(customer->m_title) != 0) {
        return false;
    }
    if (m_name.compare(customer->m_name) != 0) {
        return false;
    }
    if (m_surname.compare(customer->m_surname) != 0) {
        return false;
    }
    if (m_organisation.compare(customer->m_organisation) != 0) {
        return false;
    }
    if (m_street.compare(customer->m_street) != 0) {
        return false;
    }
    if (m_city.compare(customer->m_city) != 0) {
        return false;
    }
    if (m_mail.compare(customer->m_mail) != 0) {
        return false;
    }

    return true;
}






