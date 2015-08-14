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

    /**
     * @return returns the identifier
     */
    int id() const;

    /**
     * @brief sets the identifier
     * @param id identifier
     */
    void setId(int id);

    /**
     * @return returns the net costs per unit (cost without tax)
     */
    Decimal netCostPerUnit() const;

    /**
     * @brief sets the costs per unit (with tax)
     * @param costPerUnit cost per unit
     */
    void setCostPerUnit(Decimal costPerUnit);

    /**
     * @return returns the costs per unit (with tax)
     */
    Decimal costPerUnit() const;

    /**
     * @return returns the name
     */
    QString name() const;

    /**
     * @param name sets the name
     */
    void setName(const QString &name);

    /**
     * @return returns the type description (can be empty)
     */
    QString type() const;

    /**
     * @brief sets the type description
     * @param type type description
     */
    void setType(const QString &type);

    /**
     * @return returns the unit (can be empty)
     */
    QString unit() const;

    /**
     * @brief sets the unit
     * @param unit unit
     */
    void setUnit(const QString &unit);

    /**
     * @return returns the manufactor (can be empty)
     */
    QString manufactor() const;

    /**
     * @brief sets the manufactor
     * @param manufactor manufactor
     */
    void setManufactor(const QString &manufactor);

    /**
     * @return returns a string representation of this object
     */
    QString toString() const;

    /**
     * @param material
     * @return returns true if this and the parameter are equal
     */
    bool equals(const Material::Ptr material) const;

    /**
     * @return returns the article number
     */
    QString articleNumber() const;

    /**
     * @brief sets the article number
     * @param articleNumber article number
     */
    void setArticleNumber(const QString &articleNumber);

    /**
     * @return returns the taxRate in percent (between 0 and 1)
     */
    double taxRate() const;

    /**
     * @brief sets the taxrate
     * @param taxRate tax rate (between 0 and 1)
     */
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
