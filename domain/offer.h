#ifndef OFFER_H
#define OFFER_H

#include <memory.h>
#include <QDate>

#include "domain/customer.h"
#include "domain/billitem.h"

class Offer
{
public:
    typedef std::shared_ptr<Offer> Ptr;
    Offer();

    /**
     * @return returns the recipient
     */
    Customer::Ptr customer() const;

    /**
     * @brief sets the recipient
     * @param customer recipient
     */
    void setCustomer(const Customer::Ptr &customer);

    /**
     * @return returns the items
     */
    QList<BillItem::Ptr> items() const;

    /**
     * @brief sets the items
     * @param items items
     */
    void setItems(const QList<BillItem::Ptr> &items);

    /**
     * @return returns the totalPrice (with tax)
     */
    Decimal totalPrice() const;

    /**
     * @return returns the totalPrice (without tax)
     */
    Decimal netPrice() const;

    /**
     * @return returns all existing taxrates (keys)
     *         and the amount of each taxrate which is included in
     *         Offer::totalPrice() (value)
     */
    QMap<double, Decimal> inTotalPriceIncludedTaxes() const;

    /**
     * @return returns the offer date
     */
    QDate date() const;

    /**
     * @brief sets the offer date
     * @param date offer date
     */
    void setDate(const QDate &date);

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
     * @return returns a string representation of this object
     */
    QString toString();

    /**
     * @param offer
     * @return returns true if this and the parameter are equal
     */
    bool equals(const Offer::Ptr offer) const;

private:
    int m_id;
    Customer::Ptr m_customer;
    QList<BillItem::Ptr> m_items;
    QDate m_date;
};
Q_DECLARE_METATYPE(Offer::Ptr)

#endif // OFFER_H
