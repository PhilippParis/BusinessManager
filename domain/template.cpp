#include "template.h"

Template::Template()
{

}

Template::~Template()
{

}
QString Template::name() const
{
    return m_name;
}

void Template::setName(const QString &name)
{
    m_name = name;
}
QString Template::organisation() const
{
    return m_organisation;
}

void Template::setOrganisation(const QString &organisation)
{
    m_organisation = organisation;
}
QString Template::type() const
{
    return m_type;
}

void Template::setType(const QString &type)
{
    m_type = type;
}
QString Template::desc() const
{
    return m_desc;
}

void Template::setDesc(const QString &desc)
{
    m_desc = desc;
}
QMap<Product::Ptr, double> Template::material() const
{
    return m_material;
}

void Template::setMaterial(const QMap<Product::Ptr, double> &material)
{
    m_material = material;
}

QString Template::toString()
{
    return "Template{id= " + QString::number(m_id) +
           ", name= " + m_name +
           ", org= " + m_organisation +
           ", type= " + m_type +
           ", desc= " + m_desc +
            "}";
}

bool Template::equals(Template::Ptr item)
{
    if (m_id != item->m_id) {
        return false;
    }
    if (m_name.compare(item->m_name) != 0) {
        return false;
    }
    if (m_organisation.compare(item->m_organisation) != 0) {
        return false;
    }
    if (m_type.compare(item->m_type) != 0) {
        return false;
    }
    if (m_unit.compare(item->m_unit) != 0) {
        return false;
    }
    if (m_desc.compare(item->m_desc) != 0) {
        return false;
    }
    if (m_itemDesc.compare(item->m_itemDesc) != 0) {
        return false;
    }
    if (m_price != item->m_price) {
        return false;
    }
    if (m_workingHours != item->m_workingHours) {
        return false;
    }

    return true;
}

QString Template::itemDesc() const
{
    return m_itemDesc;
}

void Template::setItemDesc(const QString &itemDesc)
{
    m_itemDesc = itemDesc;
}
QString Template::unit() const
{
    return m_unit;
}

void Template::setUnit(const QString &unit)
{
    m_unit = unit;
}
double Template::workingHours() const
{
    return m_workingHours;
}

void Template::setWorkingHours(double workingHours)
{
    m_workingHours = workingHours;
}
double Template::price() const
{
    return m_price;
}

void Template::setPrice(double price)
{
    m_price = price;
}




int Template::id() const
{
    return m_id;
}

void Template::setId(int id)
{
    m_id = id;
}







