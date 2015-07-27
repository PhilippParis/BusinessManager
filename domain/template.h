#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QMap>
#include <QString>

#include "domain/product.h"

class Template
{
public:
    typedef std::shared_ptr<Template> Ptr;

    Template();
    ~Template();

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString organisation() const;
    void setOrganisation(const QString &organisation);

    QString type() const;
    void setType(const QString &type);

    QString desc() const;
    void setDesc(const QString &desc);

    QMap<Product::Ptr, double> material() const;
    void setMaterial(const QMap<Product::Ptr, double> &material);

    QString itemDesc() const;
    void setItemDesc(const QString &itemDesc);

    QString unit() const;
    void setUnit(const QString &unit);

    double workingHours() const;
    void setWorkingHours(double workingHours);

    double price() const;
    void setPrice(double price);

    QString toString();
    bool equals(Template::Ptr item);

private:
    int m_id = -1;
    QString m_name;
    QString m_organisation;
    QString m_type;
    QString m_desc;

    QString m_itemDesc;
    QString m_unit;
    double m_workingHours;
    double m_price;

    QMap<Product::Ptr, double> m_material;
};

#endif // TEMPLATE_H
