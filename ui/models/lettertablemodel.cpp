#include "lettertablemodel.h"

LetterTableModel::LetterTableModel()
{

}
int LetterTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant LetterTableModel::data(const QModelIndex &index, int role) const
{
    Letter::Ptr letter = m_data.at(index.row());

    if(role == Qt::DisplayRole) {
        switch (index.column()) {
        case Date:
            return letter->date();
        case Name:
            return letter->customer()->fullName();
        case Org:
            return letter->customer()->organisation();
        }
    }

    return QVariant();
}

QVariant LetterTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal) {
                switch (section)
                {
                case Name:
                    return tr("Name");
                case Org:
                    return tr("Organisation");
                case Date:
                    return tr("Date");
                }
            }
        }
    return QVariant();
}
