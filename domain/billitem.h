#ifndef BILLITEM_H
#define BILLITEM_H

#include <memory>
#include <QString>
#include <QMap>
#include <QMetaType>

#include "domain/product.h"

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

    void addMaterial(const Product::Ptr product, double quantity);
    void removeMaterial(const Product::Ptr product);

    QMap<Product::Ptr, double> material() const;

private:
    int m_id = -1;
    double m_workingHours = 0.0;
    double m_materialCost = 0.0;
    double m_price = 0.0;
    double m_wagePerHour = 0.0;
    double m_quantity = 0.0;
    QString m_description;
    QString m_unit;
    QMap<Product::Ptr, double> m_material;
};
Q_DECLARE_METATYPE(BillItem::Ptr)

#endif // BILLITEM_H
