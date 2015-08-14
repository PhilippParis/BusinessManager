#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <QString>
#include <QMetaType>

#include "decimal.h"

class Material
{
public:
    typedef std::shared_ptr<Material> Ptr;
    Material();

    int id() const;
    void setId(int id);

    Decimal netCostPerUnit() const;

    void setCostPerUnit(Decimal costPerUnit);
    Decimal costPerUnit() const;

    QString name() const;
    void setName(const QString &name);

    QString type() const;
    void setType(const QString &type);

    QString unit() const;
    void setUnit(const QString &unit);

    QString manufactor() const;
    void setManufactor(const QString &manufactor);

    QString toString() const;
    bool equals(const Material::Ptr material) const;

    QString articleNumber() const;
    void setArticleNumber(const QString &articleNumber);

    double taxRate() const;
    void setTaxRate(double taxRate);

private:
    int m_id = -1;
    Decimal m_costPerUnit = Decimal::fromValue(-1.0);
    double m_taxrate = -1.0;

    QString m_name;
    QString m_type = "";
    QString m_unit;
    QString m_manufactor = "";
    QString m_articleNumber = "";
};
Q_DECLARE_METATYPE(Material::Ptr)

#endif // MATERIAL_H
