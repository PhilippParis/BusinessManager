#include "product.h"

Product::Product()
{

}
int Product::id() const
{
    return m_id;
}

void Product::setId(int id)
{
    m_id = id;
}

double Product::costPerUnit() const
{
    return m_costPerUnit;
}

void Product::setCostPerUnit(double costPerUnit)
{
    m_costPerUnit = costPerUnit;
}
QString Product::name() const
{
    return m_name;
}

void Product::setName(const QString &name)
{
    m_name = name;
}
QString Product::type() const
{
    return m_type;
}

void Product::setType(const QString &type)
{
    m_type = type;
}
QString Product::unit() const
{
    return m_unit;
}

void Product::setUnit(const QString &unit)
{
    m_unit = unit;
}
QString Product::manufactor() const
{
    return m_manufactor;
}

void Product::setManufactor(const QString &desc)
{
    m_manufactor = desc;
}

QString Product::toString() const
{
    return "Product{id= " + QString::number(m_id) +
           ", cost = " + QString::number(m_costPerUnit) +
           ", tax = " + QString::number(m_tax) +
           ", name = " + m_name +
           ", type = " + m_type +
           ", unit = " + m_type +
           ", desc = " + m_type +
           "}";
}

bool Product::equals(const Product::Ptr product) const
{
    if (product == nullptr) {
        return false;
    }
    if (m_id != product->m_id) {
        return false;
    }
    if (m_costPerUnit != product->m_costPerUnit) {
        return false;
    }
    if (m_tax != product->m_tax) {
        return false;
    }
    if (m_name.compare(product->m_name) != 0) {
        return false;
    }
    if (m_type.compare(product->m_type) != 0) {
        return false;
    }
    if (m_unit.compare(product->m_unit) != 0) {
        return false;
    }
    if (m_manufactor.compare(product->m_manufactor) != 0) {
        return false;
    }
    if (m_articleNumber.compare(product->m_articleNumber) != 0) {
        return false;
    }

    return true;
}
QString Product::articleNumber() const
{
    return m_articleNumber;
}

void Product::setArticleNumber(const QString &articleNumber)
{
    m_articleNumber = articleNumber;
}
double Product::tax() const
{
    return m_tax;
}

void Product::setTax(double tax)
{
    m_tax = tax;
}


