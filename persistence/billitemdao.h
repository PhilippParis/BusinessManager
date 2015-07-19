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
    virtual bool write(BillItem::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @return true if the data was updated successfully
     */
    virtual bool update(BillItem::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @return true if the data was removed successfully
     */
    virtual bool remove(BillItem::Ptr item) = 0;

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist
     */
    virtual BillItem::Ptr get(int id) = 0;
};

#endif // BILLITEMDAO_H
