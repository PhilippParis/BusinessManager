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

    /**
     * @return returns the identifier of the bill
     */
    int id() const;

    /**
     * @brief sets the identifier of the bill
     * @param id identifier
     */
    void setId(int id);

    /**
     * @return returns the recipient of the bill
     */
    Customer::Ptr customer() const;

    /**
     * @brief sets the recipient of the bill
     * @param customer recipient
     */
    void setCustomer(const Customer::Ptr &customer);

    /**
     * @return returns the bill number
     */
    int billNumber() const;

    /**
     * @brief sets the bill number
     * @param billNumber bill number
     */
    void setBillNumber(int billNumber);

    /**
     * @return returns true if the bill was already payed
     */
    bool payed() const;

    /**
     * @brief sets if the bill was already payed
     * @param payed bill was already payed
     */
    void setPayed(bool payed);

    /**
     * @return returns the bill date
     */
    QDate date() const;

    /**
     * @brief sets the bill date
     * @param date bill date
     */
    void setDate(const QDate &date);

    /**
     * @return returns all bill items
     */
    QList<BillItem::Ptr> items() const;

    /**
     * @brief sets the bill items
     * @param items bill items
     */
    void setItems(const QList<BillItem::Ptr> &items);

    /**
     * @return returns all discounts
     */
    QList<Discount::Ptr> discounts() const;

    /**
     * @brief set the discounts
     * @param discounts discounts
     */
    void setDiscounts(const QList<Discount::Ptr> &discounts);

    /**
     * @return returns the total price inclusive all taxes
     */
    Decimal totalPrice() const;

    /**
     * @return returns the total price exclusive taxes
     */
    Decimal netPrice() const;

    /**
     * @return returns all existing taxrates (keys)
     *         and the amount of each taxrate which is included in
     *         Bill::totalPrice() (value)
     */
    QMap<double, Decimal> inTotalPriceIncludedTaxes() const;

    /**
     * @return returns a string representation of the bill
     */
    QString toString() const;

    /**
     * @return returns true if this bill is equal to the other bill
     * @param other other bill
     */
    bool equals(const Bill::Ptr other) const;

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
