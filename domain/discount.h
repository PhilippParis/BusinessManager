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

    Decimal value() const;
    void setValue(Decimal value);

    QString text() const;
    void setText(const QString &text);

    int id() const;
    void setId(int id);

    QString toString() const;
    bool equals(Discount::Ptr item) const;

private:
    int m_id = -1;
    QString m_text = "";
    Decimal m_value = Decimal::fromValue(-1.0);
};

#endif // DISCOUNT_H
