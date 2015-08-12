#ifndef LETTERSORTFILTERPROXYMODEL_H
#define LETTERSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class LetterSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    LetterSortFilterProxyModel();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // LETTERSORTFILTERPROXYMODEL_H
