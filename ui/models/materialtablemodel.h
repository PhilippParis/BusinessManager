#ifndef MATERIALTABLEMODEL_H
#define MATERIALTABLEMODEL_H

#include "ui/models/domainitemmodel.h"

#include "domain/material.h"

class MaterialTableModel : public DomainItemModel<Material::Ptr>
{
    Q_OBJECT
public:
    MaterialTableModel();
    int columnCount(const QModelIndex &parent) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &) const override;

    void addAllWithQuantity(QMap<Material::Ptr, double> materials);
    void add(Material::Ptr material, double quantity);

    void remove(Material::Ptr item) override;
    void replace(Material::Ptr old, Material::Ptr updated) override;
    void clear() override;

    QMap<Material::Ptr, double> itemsWithQuantity() const;

signals:
    void materialChanged();

private:
    enum Column {
        Name = 0, Nr, Manufactor, Type, Quantity
    };

    QMap<Material::Ptr, double> m_quantities;
};

#endif // MATERIALTABLEMODEL_H
