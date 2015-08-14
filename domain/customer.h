#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QMetaType>
#include <memory>

class Customer
{
public:
    typedef std::shared_ptr<Customer> Ptr;

    Customer();
    ~Customer();

    /**
     * @return returns the full name of the customer
     *         title + name + surname
     */
    QString fullName() const;

    /**
     * @return returns the title of the customer (can be empty)
     */
    QString title() const;

    /**
     * @brief sets the title of the customer
     * @param title title of the customer
     */
    void setTitle(const QString &title);

    /**
     * @return returns the name of the customer
     */
    QString name() const;

    /**
     * @brief sets the name of the customer
     * @param customer name
     */
    void setName(const QString &name);

    /**
     * @return returns the surname
     */
    QString surname() const;

    /**
     * @brief sets the surname
     * @param surname surname
     */
    void setSurname(const QString &surname);

    /**
     * @return returns the organisation (can be empty)
     */
    QString organisation() const;

    /**
     * @brief sets the organisation
     * @param organisation organisation
     */
    void setOrganisation(const QString &organisation);

    /**
     * @return returns the first address line (street)
     */
    QString street() const;

    /**
     * @brief sets the first address line (street)
     * @param street street
     */
    void setStreet(const QString &street);

    /**
     * @return returns the second address line (city and postal code)
     */
    QString city() const;

    /**
     * @brief sets the secon address line (city and postal code)
     * @param city city and postal code
     */
    void setCity(const QString &city);

    /**
     * @return returns the mail address (can be empty)
     */
    QString mail() const;

    /**
     * @brief sets the mail address
     * @param mail mail address
     */
    void setMail(const QString &mail);

    /**
     * @return returns the identifier
     */
    int id() const;

    /**
     * @brief sets the identifier
     * @param id identifier
     */
    void setId(int id);

    /**
     * @return returns string representation of the customer
     */
    QString toString() const;

    /**
     * @param customer other customer
     * @return returns true if this and the other customer are equal
     */
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
Q_DECLARE_METATYPE(Customer::Ptr)

#endif // CUSTOMER_H
