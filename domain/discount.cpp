#include "discount.h"

Discount::Discount()
{

}

Decimal Discount::value() const
{
    return m_value;
}

void Discount::setValue(Decimal value)
{
    m_value = value;
}

QString Discount::text() const
{
    return m_text;
}

void Discount::setText(const QString &text)
{
    m_text = text;
}
int Discount::id() const
{
    return m_id;
}

void Discount::setId(int id)
{
    m_id = id;
}

QString Discount::toString() const
{
    return "Discount{ id= " + QString::number(m_id) +
           "text= " + m_text +
           "value= " + QString::number(m_value.value()) +
           "}";
}

bool Discount::equals(Discount::Ptr item) const
{
    if (m_id != item->m_id) {
        return false;
    }

    if (m_text.compare(item->m_text) != 0) {
        return false;
    }

    if (m_value != item->m_value) {
        return false;
    }

    return true;
}




