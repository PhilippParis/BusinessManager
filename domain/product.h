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

    QString toString() const;
    bool equals(const Product::Ptr product) const;

    QString articleNumber() const;
    void setArticleNumber(const QString &articleNumber);

    double tax() const;
    void setTax(double tax);

private:
    int m_id = -1;
    double m_costPerUnit = 0.0; // net cost (without tax)
    double m_tax;               // total costs = m_costPerUnit + m_tax
    QString m_name;
    QString m_type = "";
    QString m_unit;
    QString m_manufactor = "";
    QString m_articleNumber = "";
};
Q_DECLARE_METATYPE(Product::Ptr)

#endif // PRODUCT_H
