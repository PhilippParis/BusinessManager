#ifndef BILL_H
#define BILL_H

#include <QList>
#include <memory>
#include <QMetaType>
#include <QDate>

#include "domain/customer.h"
#include "domain/billitem.h"
#include "domain/discount.h"

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

    QDate date() const;
    void setDate(const QDate &date);

    bool equals(const Bill::Ptr) const;

    QList<BillItem::Ptr> items() const;
    void setItems(const QList<BillItem::Ptr> &items);

    QList<Discount::Ptr> discounts() const;
    void setDiscounts(const QList<Discount::Ptr> &discounts);

    Decimal totalPrice() const;
    Decimal netPrice() const;

private:
    int m_id = -1;
    Customer::Ptr m_customer;
    int m_billNumber = -1;
    QDate m_date;
    bool m_payed;
    QList<BillItem::Ptr> m_items;
    QList<Discount::Ptr> m_discounts;

};
Q_DECLARE_METATYPE(Bill::Ptr)

#endif // BILL_H
