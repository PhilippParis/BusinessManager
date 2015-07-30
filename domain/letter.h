#ifndef LETTER_H
#define LETTER_H

#include <memory>
#include <QTextDocument>

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

private:
    Customer::Ptr m_customer;
    QTextDocument *m_textDoc;
};

#endif // LETTER_H
