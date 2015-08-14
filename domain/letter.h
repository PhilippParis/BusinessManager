#ifndef LETTER_H
#define LETTER_H

#include <memory>
#include <QTextDocument>
#include <QDate>

#include "domain/customer.h"

class Letter
{
public:
    typedef std::shared_ptr<Letter> Ptr;
    Letter();
    ~Letter();

    /**
     * @return returns the recipient
     */
    Customer::Ptr customer() const;

    /**
     * @brief sets the recipient
     * @param customer recipient
     */
    void setCustomer(Customer::Ptr customer);

    /**
     * @return returns the letter text document
     */
    QTextDocument *textDoc() const;

    /**
     * @brief sets the letter text document
     * @param textDoc text document
     */
    void setTextDoc(QTextDocument *textDoc);

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
     * @return returns the date the letter was written
     */
    QDate date() const;

    /**
     * @brief sets the letter date
     * @param date date
     */
    void setDate(const QDate &date);

    /**
     * @return returns a string representation of this object
     */
    QString toString();

    /**
     * @param letter letter
     * @return returns true if this and the parameter are equal
     */
    bool equals(const Letter::Ptr letter) const;

private:
    int m_id = -1;
    QDate m_date;
    Customer::Ptr m_customer;
    QTextDocument *m_textDoc;
};

#endif // LETTER_H
