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
int Product::stock() const
{
    return m_stock;
}

void Product::setStock(int stock)
{
    m_stock = stock;
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
QString Product::desc() const
{
    return m_desc;
}

void Product::setDesc(const QString &desc)
{
    m_desc = desc;
}
double Product::pricePerUnit() const
{
    return m_pricePerUnit;
}

void Product::setPricePerUnit(double pricePerUnit)
{
    m_pricePerUnit = pricePerUnit;
}

QString Product::toString() const
{
    return "Product{id= " + QString::number(m_id) +
           ", cost = " + QString::number(m_costPerUnit) +
           ", price = " + QString::number(m_pricePerUnit) +
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
    if (m_pricePerUnit != product->m_pricePerUnit) {
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
    if (m_desc.compare(product->m_desc) != 0) {
        return false;
    }

    return true;
}
