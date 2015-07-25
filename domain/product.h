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

    double costPerUnit() const;
    void setCostPerUnit(double costPerUnit);

    QString name() const;
    void setName(const QString &name);

    QString type() const;
    void setType(const QString &type);

    QString unit() const;
    void setUnit(const QString &unit);

    QString manufactor() const;
    void setManufactor(const QString &manufactor);

    double pricePerUnit() const;
    void setPricePerUnit(double pricePerUnit);

    QString toString() const;
    bool equals(const Product::Ptr product) const;

    QString articleNumber() const;
    void setArticleNumber(const QString &articleNumber);

private:
    int m_id = -1;
    double m_costPerUnit = 0.0;
    double m_pricePerUnit = 0.0;
    QString m_name;
    QString m_type = "";
    QString m_unit;
    QString m_manufactor = "";
    QString m_articleNumber = "";
};
Q_DECLARE_METATYPE(Product::Ptr)

#endif // PRODUCT_H
