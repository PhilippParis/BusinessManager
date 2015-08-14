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

Decimal BillItem::materialCost() const
{
    return m_materialCost;
}

void BillItem::setMaterialCost(Decimal materialCost)
{
    m_materialCost = materialCost;
}

Decimal BillItem::materialNetCost() const
{
    return m_materialNetCost;
}

void BillItem::setMaterialNetCost(Decimal materialCost)
{
    m_materialNetCost = materialCost;
}

Decimal BillItem::wagePerHour() const
{
    return m_wagePerHour;
}

void BillItem::setWagePerHour(Decimal wagePerHour)
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

Decimal BillItem::price() const
{
    return m_price;
}

void BillItem::setPrice(Decimal price)
{
    m_price = price;
}

Decimal BillItem::netPrice() const
{
    return m_price / (1.0 + m_taxRate);
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
           ", cost=" + QString::number(m_materialNetCost.value()) +
           ", price=" + QString::number(m_price.value()) +
           ", unit=" + m_unit +
           ", quantity=" + QString::number(m_quantity) +
           ", workingHours=" + QString::number(m_workingHours) +
           ", wage=" + QString::number(m_wagePerHour.value()) +
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
    if (m_materialNetCost != item->m_materialNetCost) {
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
    if (m_materialOverhead != item->m_materialOverhead) {
        return false;
    }
    if (m_factoryOverhead != item->m_factoryOverhead) {
        return false;
    }
    if (m_taxRate != item->m_taxRate) {
        return false;
    }
    if (m_cashback != item->m_cashback) {
        return false;
    }

    return true;
}

QMap<Material::Ptr, double> BillItem::material() const
{
    return m_material;
}

void BillItem::setMaterial(const QMap<Material::Ptr, double> &material)
{
    m_material = material;
}
double BillItem::materialOverhead() const
{
    return m_materialOverhead;
}

void BillItem::setMaterialOverhead(double material_overhead)
{
    m_materialOverhead = material_overhead;
}

double BillItem::factoryOverhead() const
{
    return m_factoryOverhead;
}

void BillItem::setFactoryOverhead(double factory_overhead)
{
    m_factoryOverhead = factory_overhead;
}

double BillItem::profit() const
{
    return m_profit;
}

void BillItem::setProfit(double profit)
{
    m_profit = profit;
}

double BillItem::cashback() const
{
    return m_cashback;
}

void BillItem::setCashback(double cashback)
{
    m_cashback = cashback;
}

double BillItem::taxRate() const
{
    return m_taxRate;
}

void BillItem::setTaxRate(double tax)
{
    m_taxRate = tax;
}

Decimal BillItem::materialExpenses()
{
    return m_materialCost * (1.0 + m_materialOverhead);
}

Decimal BillItem::factoryExpenses()
{
    return (m_wagePerHour * m_workingHours) * (1.0 + m_factoryOverhead);
}

Decimal BillItem::costs()
{
    return materialExpenses() + factoryExpenses();
}

Decimal BillItem::calculatedPrice()
{
    Decimal costWithProfit = costs() * (1.0 + m_profit);
    Decimal costWithCashback = costWithProfit * (1.0 + m_cashback);
    return costWithCashback * (1.0 + m_taxRate);
}


















