#ifndef TEMPLATETABLEMODEL_H
#define TEMPLATETABLEMODEL_H

#include <QObject>
#include <QDebug>

#include "ui/models/domainitemmodel.h"

#include "domain/template.h"

class TemplateTableModel : public DomainItemModel<Template::Ptr>
{
    Q_OBJECT
public:
    TemplateTableModel();
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    enum Column {
        Name = 0, Org, Type, Desc
    };
};

#endif // TEMPLATETABLEMODEL_H
