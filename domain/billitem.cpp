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
Bill::Ptr BillItem::bill() const
{
    return m_bill;
}

void BillItem::setBill(const Bill::Ptr bill)
{
    m_bill = bill;
}

QString BillItem::toString() const
{
    return "BillItem{id=" + QString::number(m_id) +
           ", desc=" + m_description +
           ", cost=" + QString::number(m_materialCost) +
           ", price=" + QString::number(m_price) +
           ", unit=" + m_unit +
           ", quantity=" + m_quantity +
           ", workingHours=" + QString::number(m_workingHours) +
           ", wage=" + QString::number(m_wagePerHour) +
           ", bill=" + (m_bill == nullptr? "null" : m_bill->toString()) +
           "}";
}










