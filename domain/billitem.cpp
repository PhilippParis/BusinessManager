#include "billitem.h"

BillItem::BillItem()
{

}

BillItem::~BillItem()
{

}
int BillItem::id() const
{
    return m_id;
}

void BillItem::setId(int id)
{
    m_id = id;
}

double BillItem::workingHours() const
{
    return m_workingHours;
}

void BillItem::setWorkingHours(double workingHours)
{
    m_workingHours = workingHours;
}

double BillItem::materialCost() const
{
    return m_materialCost;
}

void BillItem::setMaterialCost(double materialCost)
{
    m_materialCost = materialCost;
}

double BillItem::wagePerHour() const
{
    return m_wagePerHour;
}

void BillItem::setWagePerHour(double wagePerHour)
{
    m_wagePerHour = wagePerHour;
}

QString BillItem::description() const
{
    return m_description;
}

void BillItem::setDescription(const QString &description)
{
    m_description = description;
}

QString BillItem::unit() const
{
    return m_unit;
}

void BillItem::setUnit(const QString &unit)
{
    m_unit = unit;
}

double BillItem::price() const
{
    return m_price;
}

void BillItem::setPrice(double price)
{
    m_price = price;
}
double BillItem::quantity() const
{
    return m_quantity;
}

void BillItem::setQuantity(double quantity)
{
    m_quantity = quantity;
}

QString BillItem::toString() const
{
    return "BillItem{id=" + QString::number(m_id) +
           ", desc=" + m_description +
           ", cost=" + QString::number(m_materialCost) +
           ", price=" + QString::number(m_price) +
           ", unit=" + m_unit +
           ", quantity=" + QString::number(m_quantity) +
           ", workingHours=" + QString::number(m_workingHours) +
           ", wage=" + QString::number(m_wagePerHour) +
            "}";
}

bool BillItem::equals(const BillItem::Ptr item) const
{
    if(item == nullptr) {
        return false;
    }
    if (m_id != item->m_id) {
        return false;
    }
    if (m_description.compare(item->m_description) != 0) {
        return false;
    }
    if (m_materialCost != item->m_materialCost) {
        return false;
    }
    if (m_price != item->m_price) {
        return false;
    }
    if (m_unit.compare(item->m_unit) != 0) {
        return false;
    }
    if (m_quantity != item->m_quantity) {
        return false;
    }
    if (m_workingHours != item->m_workingHours) {
        return false;
    }
    if (m_wagePerHour != item->m_wagePerHour) {
        return false;
    }

    return true;
}

void BillItem::addMaterial(const Product::Ptr product, double quantity)
{
    m_material.insert(product, quantity);
}

void BillItem::removeMaterial(const Product::Ptr product)
{
    m_material.remove(product);
}
QMap<Product::Ptr, double> BillItem::material() const
{
    return m_material;
}











