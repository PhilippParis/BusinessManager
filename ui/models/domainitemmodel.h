#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

template <typename T>
class DomainItemModel : public QAbstractTableModel
{
public:
    DomainItemModel()
    {

    }

    int rowCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        return m_data.size();
    }

    void addAll(QList<T> items)
    {
        beginInsertRows(QModelIndex(), 0, items.size() - 1);
        m_data = items;
        endInsertRows();
    }

    QModelIndex add(T item)
    {
        beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
        m_data.append(item);
        endInsertRows();

        return index(m_data.size() - 1, 0);
    }

    void remove(T item)
    {
        int row = m_data.indexOf(item);
        beginRemoveRows(QModelIndex(), row, row);
        m_data.removeOne(item);
        endRemoveRows();
    }

    void replace(T old, T updated)
    {
        int row = m_data.indexOf(old);
        m_data.replace(row, updated);
        emit dataChanged(index(0, row), index(4, row));
    }

    T get(QModelIndex index)
    {
        return m_data.at(index.row());
    }

    int indexOf(T item)
    {
        for(int i = 0; i < m_data.size(); ++i) {
            if(m_data.at(i)->id() == item->id()) {
                return i;
            }
        }
        return -1;
    }

    void clear()
    {
        beginRemoveRows(QModelIndex(), 0, m_data.size() - 1);
        m_data.clear();
        endRemoveRows();
    }

    QList<T> items()
    {
        return m_data;
    }

protected:
    QList<T> m_data;
};

#endif // TABLEMODEL_H
