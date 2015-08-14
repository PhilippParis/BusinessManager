#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <memory>
#include <QString>

#include "decimal.h"

class Discount
{
public:
    typedef std::shared_ptr<Discount> Ptr;
    Discount();

    /**
     * @return returns the discount value
     */
    Decimal value() const;

    /**
     * @brief sets the discount value
     * @param value discount value
     */
    void setValue(Decimal value);

    /**
     * @return returns the discount text
     *         (e.g. coupon, bulk discount,...)
     */
    QString text() const;

    /**
     * @brief set discount text
     * @param text text (e.g. coupon, bulk discount,...)
     */
    void setText(const QString &text);

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
     * @return returns a string representation of
     * the discount object
     */
    QString toString() const;

    /**
     * @param item discount
     * @return true if this and item are equal
     */
    bool equals(Discount::Ptr item) const;

private:
    int m_id = -1;
    QString m_text = "";
    Decimal m_value = Decimal::fromValue(-1.0);
};

#endif // DISCOUNT_H
