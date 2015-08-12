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

    Customer::Ptr customer() const;
    void setCustomer(Customer::Ptr customer);

    QTextDocument *textDoc() const;
    void setTextDoc(QTextDocument *textDoc);

    int id() const;
    void setId(int id);

    QDate date() const;
    void setDate(const QDate &date);

    QString toString();
    bool equals(const Letter::Ptr letter) const;

private:
    int m_id = -1;
    QDate m_date;
    Customer::Ptr m_customer;
    QTextDocument *m_textDoc;
};

#endif // LETTER_H
