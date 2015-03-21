#ifndef BILLITEMDAO_H
#define BILLITEMDAO_H

#include <QMap>

#include "domain/billitem.h"

class BillItemDAO
{
public:
    BillItemDAO();
    ~BillItemDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @return true if the data was written succesfully
     */
    bool write(BillItem::Ptr item);

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @return true if the data was updated successfully
     */
    bool update(BillItem::Ptr item);

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @return true if the data was removed successfully
     */
    bool remove(BillItem::Ptr item);

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist
     */
    BillItem::Ptr get(int id);

private:
    /**
     * @brief creates a new billitem from the data in the underlying data source
     * @param id id of the billitem
     * @return a new billitem or null if there was an error
     */
    virtual BillItem::Ptr getFromDataSource(int id) = 0;

    /**
     * @brief writes a billitem into the data source
     * @param item item to write
     * @return true if the billitem was written successfully
     */
    virtual bool writeToDataSource(BillItem::Ptr item) = 0;

    /**
     * @brief udpates the data in the data source
     * @param item data to update
     * @return true if the data was updated successfully
     */
    virtual bool updateInDataSource(BillItem::Ptr item) = 0;

    /**
     * @brief removes a billitem from the data source
     * @param item item to remove
     * @return true if the item was removed successfully
     */
    virtual bool removeFromDataSource(BillItem::Ptr item) = 0;

private:
    QMap<int, BillItem::Ptr> m_dataBuffer;      /// buffer of billitems
};

#endif // BILLITEMDAO_H
