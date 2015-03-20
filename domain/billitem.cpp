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








