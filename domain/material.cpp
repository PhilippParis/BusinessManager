#include "material.h"

Material::Material()
{

}
int Material::id() const
{
    return m_id;
}

void Material::setId(int id)
{
    m_id = id;
}

Decimal Material::netCostPerUnit() const
{
    return m_costPerUnit / (1.0 + m_taxrate);
}

void Material::setCostPerUnit(Decimal costPerUnit)
{
    m_costPerUnit = costPerUnit;
}

Decimal Material::costPerUnit() const
{
    return m_costPerUnit;
}

QString Material::name() const
{
    return m_name;
}

void Material::setName(const QString &name)
{
    m_name = name;
}
QString Material::type() const
{
    return m_type;
}

void Material::setType(const QString &type)
{
    m_type = type;
}
QString Material::unit() const
{
    return m_unit;
}

void Material::setUnit(const QString &unit)
{
    m_unit = unit;
}
QString Material::manufactor() const
{
    return m_manufactor;
}

void Material::setManufactor(const QString &desc)
{
    m_manufactor = desc;
}

QString Material::toString() const
{
    return "Material{id= " + QString::number(m_id) +
           ", cost = " + QString::number(m_costPerUnit.value()) +
           ", taxrate = " + QString::number(m_taxrate) +
           ", name = " + m_name +
           ", type = " + m_type +
           ", unit = " + m_type +
           ", desc = " + m_type +
           "}";
}

bool Material::equals(const Material::Ptr material) const
{
    if (material == nullptr) {
        return false;
    }
    if (m_id != material->m_id) {
        return false;
    }
    if (m_costPerUnit != material->m_costPerUnit) {
        return false;
    }
    if (m_taxrate != material->m_taxrate) {
        return false;
    }
    if (m_name.compare(material->m_name) != 0) {
        return false;
    }
    if (m_type.compare(material->m_type) != 0) {
        return false;
    }
    if (m_unit.compare(material->m_unit) != 0) {
        return false;
    }
    if (m_manufactor.compare(material->m_manufactor) != 0) {
        return false;
    }
    if (m_articleNumber.compare(material->m_articleNumber) != 0) {
        return false;
    }

    return true;
}
QString Material::articleNumber() const
{
    return m_articleNumber;
}

void Material::setArticleNumber(const QString &articleNumber)
{
    m_articleNumber = articleNumber;
}

double Material::taxRate() const
{
    return m_taxrate;
}

void Material::setTaxRate(double taxrate)
{
    m_taxrate = taxrate;
}


