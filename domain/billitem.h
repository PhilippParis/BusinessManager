#ifndef BILLITEM_H
#define BILLITEM_H

#include <memory>
#include <QString>
#include <QMap>
#include <QMetaType>

#include "domain/material.h"

class BillItem
{
public:
    typedef std::shared_ptr<BillItem> Ptr;

    BillItem();
    ~BillItem();

    int id() const;
    void setId(int id);

    double workingHours() const;
    void setWorkingHours(double workingHours);

    double materialCost() const;
    void setMaterialCost(double materialCost);

    double wagePerHour() const;
    void setWagePerHour(double wagePerHour);

    QString description() const;
    void setDescription(const QString &description);

    QString unit() const;
    void setUnit(const QString &unit);

    double price() const;
    void setPrice(double price);

    double quantity() const;
    void setQuantity(double quantity);

    QString toString() const;
    bool equals(const BillItem::Ptr item) const;

    QMap<Material::Ptr, double> material() const;
    void setMaterial(const QMap<Material::Ptr, double> &material);

    double materialOverhead() const;
    void setMaterialOverhead(double materialOverhead);

    double factoryOverhead() const;
    void setFactoryOverhead(double factoryOverhead);

    double profit() const;
    void setProfit(double profit);

    double cashback() const;
    void setCashback(double cashback);

    double tax() const;
    void setTax(double tax);

    double costs();
    double calculatedPrice();

private:
    int m_id = -1;

    double m_materialOverhead = -1.0;
    double m_factoryOverhead = -1.0;
    double m_profit = -1.0;
    double m_cashback = -1.0;
    double m_tax = -1.0;
    double m_price = -1.0;

    double m_workingHours = -1.0;
    double m_wagePerHour = -1.0;
    double m_materialCost = -1.0;

    double m_quantity = 0.0;
    QString m_description;
    QString m_unit;
    QMap<Material::Ptr, double> m_material;
};
Q_DECLARE_METATYPE(BillItem::Ptr)

#endif // BILLITEM_H
