#ifndef BILL_H
#define BILL_H

#include <QList>
#include <memory>

#include "domain/customer.h"
#include "domain/billitem.h"

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

    double discount() const;
    void setDiscount(double discount);

    QString discountText() const;
    void setDiscountText(const QString &discountText);

    QList<BillItem::Ptr> billItems() const;
    void addBillItem(const BillItem::Ptr &item);
    void removeBillItem(const BillItem::Ptr &item);

    int id() const;
    void setId(int id);

private:
    int m_id = -1;
    Customer::Ptr m_customer;
    QList<BillItem::Ptr> m_items;
    int m_billNumber;
    bool m_payed;
    double m_discount = 0.0;
    QString m_discountText;
};

#endif // BILL_H
