#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QMap>
#include <QString>

#include "domain/material.h"

class Template
{
public:
    typedef std::shared_ptr<Template> Ptr;

    Template();
    ~Template();

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
     * @return returns the name
     */
    QString name() const;

    /**
     * @brief sets the name
     * @param name name
     */
    void setName(const QString &name);

    /**
     * @return returns the organisation
     */
    QString organisation() const;

    /**
     * @brief sets the organisation
     * @param organisation organisation
     */
    void setOrganisation(const QString &organisation);

    /**
     * @return returns the type description
     */
    QString type() const;

    /**
     * @brief sets the type description
     * @param type type description
     */
    void setType(const QString &type);

    /**
     * @return returns the description of the template
     */
    QString desc() const;

    /**
     * @brief sets the description of the template
     * @param desc description
     */
    void setDesc(const QString &desc);

    /**
     * @return returns the material (material, quantity)
     */
    QMap<Material::Ptr, double> material() const;

    /**
     * @brief sets the material (material, quantity)
     * @param material
     */
    void setMaterial(const QMap<Material::Ptr, double> &material);

    /**
     * @return returns the article description
     */
    QString itemDesc() const;

    /**
     * @brief sets the article description
     * @param itemDesc article description
     */
    void setItemDesc(const QString &itemDesc);

    /**
     * @return returns the unit of the article
     */
    QString unit() const;

    /**
     * @brief sets the unit of the article
     * @param unit unit
     */
    void setUnit(const QString &unit);

    /**
     * @return returns the working hours needed to create the article
     */
    double workingHours() const;

    /**
     * @brief sets the working hours
     * @param workingHours working hours needed to create the article
     */
    void setWorkingHours(double workingHours);

    /**
     * @return returns the price per unit
     */
    Decimal price() const;

    /**
     * @brief sets the price per unit
     * @param price price per unit
     */
    void setPrice(Decimal price);

    /**
     * @return returns a string representation of this object
     */
    QString toString();

    /**
     * @param item item
     * @return returns true if this and the parameter are equal
     */
    bool equals(Template::Ptr item);

    /**
     * @return returns the taxrate in percent  (between 0 and 1)
     */
    double taxRate() const;

    /**
     * @brief sets the taxrate
     * @param taxRate tax rate (between 0 and 1)
     */
    void setTaxRate(double taxRate);

private:
    int m_id = -1;
    QString m_name;
    QString m_organisation = "";
    QString m_type = "";
    QString m_desc = "";

    QString m_itemDesc;
    QString m_unit;
    double m_workingHours;
    double m_taxRate;
    Decimal m_price;

    QMap<Material::Ptr, double> m_material;
};

#endif // TEMPLATE_H
