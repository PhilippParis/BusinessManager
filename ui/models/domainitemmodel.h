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

    virtual int rowCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        return m_data.size();
    }

    virtual void addAll(QList<T> items)
    {
        clear();
        if (items.isEmpty()) {
            return;
        }
        beginInsertRows(QModelIndex(), 0, items.size() - 1);
        m_data = items;
        endInsertRows();
    }

    virtual QModelIndex add(T item)
    {
        beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
        m_data.append(item);
        endInsertRows();

        return index(m_data.size() - 1, 0);
    }

    virtual void remove(T item)
    {
        int row = m_data.indexOf(item);
        beginRemoveRows(QModelIndex(), row, row);
        m_data.removeOne(item);
        endRemoveRows();
    }

    virtual void replace(T old, T updated)
    {
        int row = m_data.indexOf(old);
        m_data.replace(row, updated);
        emit dataChanged(index(0, row), index(columnCount(), row));
    }

    virtual void update(T item)
    {
        int row = indexOf(item);
        m_data.replace(row, item);
        emit dataChanged(index(0, row), index(columnCount(), row));
    }

    virtual T get(QModelIndex index)
    {
        if (!index.isValid()) {
            return nullptr;
        }
        return m_data.at(index.row());
    }

    virtual int indexOf(T item)
    {
        for(int i = 0; i < m_data.size(); ++i) {
            if(m_data.at(i)->id() == item->id()) {
                return i;
            }
        }
        return -1;
    }

    virtual void clear()
    {
        if (m_data.isEmpty()) {
            return;
        }
        beginRemoveRows(QModelIndex(), 0, m_data.size() - 1);
        m_data.clear();
        endRemoveRows();
    }

    virtual QList<T> items()
    {
        return m_data;
    }

protected:
    QList<T> m_data;
};

#endif // TABLEMODEL_H
