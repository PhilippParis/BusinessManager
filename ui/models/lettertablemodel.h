#ifndef LETTERTABLEMODEL_H
#define LETTERTABLEMODEL_H

#include "ui/models/domainitemmodel.h"
#include "domain/letter.h"

class LetterTableModel : public DomainItemModel<Letter::Ptr>
{
    Q_OBJECT
public:
    LetterTableModel();
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    enum Column {
        Date, Name, Org
    };
};

#endif // LETTERTABLEMODEL_H
