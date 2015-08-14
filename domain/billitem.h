#ifndef BILLITEM_H
#define BILLITEM_H

#include <memory>
#include <QString>
#include <QMap>
#include <QMetaType>

#include "domain/material.h"
#include "decimal.h"

class BillItem
{
public:
    typedef std::shared_ptr<BillItem> Ptr;

    BillItem();
    ~BillItem();

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
     * @return returns the working hours needed to create one article
     */
    double workingHours() const;

    /**
     * @brief sets the working hours needed to create one article
     * @param workingHours working hours
     */
    void setWorkingHours(double workingHours);

    /**
     * @return returns the material costs per article
     */
    Decimal materialCost() const;

    /**
     * @brief sets the material costs per article
     * @param materialCost material costs
     */
    void setMaterialCost(Decimal materialCost);

    /**
     * @return returns the material net costs per article
     */
    Decimal materialNetCost() const;

    /**
     * @brief sets the material net costs per article
     * @param materialCost material net costs
     */
    void setMaterialNetCost(Decimal materialNetCost);

    /**
     * @return returns the wage per hour
     */
    Decimal wagePerHour() const;

    /**
     * @brief sets the wage per hour
     * @param wagePerHour wage per hour
     */
    void setWagePerHour(Decimal wagePerHour);

    /**
     * @return returns the item description
     *         which will be visible on the bill
     */
    QString description() const;

    /**
     * @brief sets the item description
     *        which will be visible on the bill
     * @param description description
     */
    void setDescription(const QString &description);

    /**
     * @return returns the unit in which this item is sold
     */
    QString unit() const;

    /**
     * @brief sets the unit in which this item is sold
     * @param unit unit
     */
    void setUnit(const QString &unit);

    /**
     * @return returns the price of the item (incl. tax)
     */
    Decimal price() const;

    /**
     * @brief sets the price of the item (incl. tax)
     * @param price price of the item
     */
    void setPrice(Decimal price);

    /**
     * @return returns the net-price of the item (without tax)
     */
    Decimal netPrice() const;

    /**
     * @return returns the order amount
     */
    double quantity() const;

    /**
     * @brief sets the order amount
     * @param quantity amount
     */
    void setQuantity(double quantity);

    /**
     * @return returns the material used to create one article
     */
    QMap<Material::Ptr, double> material() const;

    /**
     * @brief sets the material (material, quantity) used to create on article
     * @param material material
     */
    void setMaterial(const QMap<Material::Ptr, double> &material);

    /**
     * @return returns the material overhead in percent (between 0 and 1)
     */
    double materialOverhead() const;

    /**
     * @brief sets the material overhead in percent
     * @param materialOverhead material overhead (between 0 and 1)
     */
    void setMaterialOverhead(double materialOverhead);

    /**
     * @return returns the factory overhead in percent (between 0 and 1)
     */
    double factoryOverhead() const;

    /**
     * @brief sets the factory overhead in percent
     * @param factoryOverhead factory overhead (between 0 and 1)
     */
    void setFactoryOverhead(double factoryOverhead);

    /**
     * @return returns the profit in percent (between 0 and 1)
     */
    double profit() const;

    /**
     * @brief sets the profit in percent
     * @param profit profit (between 0 and 1)
     */
    void setProfit(double profit);

    /**
     * @return returns the cashback in percent (between 0 and 1)
     */
    double cashback() const;

    /**
     * @brief sets the cashback in percent
     * @param cashback cashback( between 0 and 1)
     */
    void setCashback(double cashback);

    /**
     * @return returns the taxrate used for this item in percent (between 0 and 1)
     */
    double taxRate() const;

    /**
     * @brief sets the taxrate in percent
     * @param taxRate tax rate (between 0 and 1)
     */
    void setTaxRate(double taxRate);

    /**
     * @return calculates and returns the material expenses for one article
     */
    Decimal materialExpenses();

    /**
     * @return calculates and returns the factory expenses for one article
     */
    Decimal factoryExpenses();

    /**
     * @return calculates and returns the total costs for one article
     */
    Decimal costs();

    /**
     * @return calculates and returns the recommended price for one article
     */
    Decimal calculatedPrice();

    /**
     * @return returns the string representation of the billitem
     */
    QString toString() const;

    /**
     * @param item other item
     * @return returns true if this item and the other item are equal
     */
    bool equals(const BillItem::Ptr item) const;

private:
    int m_id = -1;

    double m_materialOverhead = -1.0;
    double m_factoryOverhead = -1.0;
    double m_profit = -1.0;
    double m_cashback = -1.0;
    double m_taxRate = -1.0;
    Decimal m_price = Decimal::fromValue(-1.0);

    double m_workingHours = -1.0;
    Decimal m_wagePerHour = Decimal::fromValue(-1.0);
    Decimal m_materialNetCost = Decimal::fromValue(-1.0);
    Decimal m_materialCost = Decimal::fromValue(-1.0);

    double m_quantity = 0.0;
    QString m_description;
    QString m_unit;
    QMap<Material::Ptr, double> m_material;
};
Q_DECLARE_METATYPE(BillItem::Ptr)

#endif // BILLITEM_H
