#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <memory>

class Customer
{
public:
    typedef std::shared_ptr<Customer> Ptr;

    Customer();
    ~Customer();

    QString title() const;
    void setTitle(const QString &title);

    QString name() const;
    void setName(const QString &name);

    QString surname() const;
    void setSurname(const QString &surname);

    QString organisation() const;
    void setOrganisation(const QString &organisation);

    QString street() const;
    void setStreet(const QString &street);

    QString city() const;
    void setCity(const QString &city);

    QString mail() const;
    void setMail(const QString &mail);

    int id() const;
    void setId(int id);

    QString toString() const;
    bool equals(Customer::Ptr customer) const;

private:
    int m_id = -1;

    // about
    QString m_title;
    QString m_name;
    QString m_surname;
    QString m_organisation;

    // address info
    QString m_street;
    QString m_city;

    QString m_mail;
};

#endif // CUSTOMER_H
