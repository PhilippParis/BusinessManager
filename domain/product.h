#ifndef PRODUCT_H
#define PRODUCT_H

#include <memory>
#include <QString>
#include <QMetaType>

class Product
{
public:
    typedef std::shared_ptr<Product> Ptr;
    Product();

    int id() const;
    void setId(int id);

    int stock() const;
    void setStock(int stock);

    double costPerUnit() const;
    void setCostPerUnit(double costPerUnit);

    QString name() const;
    void setName(const QString &name);

    QString type() const;
    void setType(const QString &type);

    QString unit() const;
    void setUnit(const QString &unit);

    QString desc() const;
    void setDesc(const QString &desc);

    double pricePerUnit() const;
    void setPricePerUnit(double pricePerUnit);

    QString toString() const;
    bool equals(const Product::Ptr product) const;

private:
    int m_id = -1;
    int m_stock = 0;
    double m_costPerUnit = 0.0;
    double m_pricePerUnit = 0.0;
    QString m_name;
    QString m_type = "";
    QString m_unit;
    QString m_desc = "";
};
Q_DECLARE_METATYPE(Product::Ptr)

#endif // PRODUCT_H
