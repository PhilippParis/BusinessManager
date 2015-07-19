#ifndef BILL_H
#define BILL_H

#include <QList>
#include <memory>
#include <QMetaType>
#include <QDate>

#include "domain/customer.h"

class Bill
{
public:
    typedef std::shared_ptr<Bill> Ptr;

    Bill();
    ~Bill();

    Customer::Ptr customer() const;
    void setCustomer(const Customer::Ptr &customer);

    int billNumber() const;
    void setBillNumber(int billNumber);

    bool payed() const;
    void setPayed(bool payed);

    int id() const;
    void setId(int id);

    QString toString() const;

private:
    int m_id = -1;
    Customer::Ptr m_customer;
    int m_billNumber;
    QDate m_date;
    bool m_payed;
};

Q_DECLARE_METATYPE(Bill::Ptr)
#endif // BILL_H
