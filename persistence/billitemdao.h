#ifndef BILLITEMDAO_H
#define BILLITEMDAO_H

#include "domain/billitem.h"
#include "persistence/persistenceexception.h"

class BillItemDAO
{
public:
    typedef std::shared_ptr<BillItemDAO> Ptr;

    BillItemDAO();
    ~BillItemDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @return true if the data was written succesfully
     */
    virtual void create(BillItem::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @return true if the data was updated successfully
     */
    virtual void update(BillItem::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @return true if the data was removed successfully
     */
    virtual void remove(BillItem::Ptr item) = 0;

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist / an error occurred
     */
    virtual BillItem::Ptr get(int id) = 0;

    /**
     * @return returns all items from the underlying datasource
     */
    virtual QList<BillItem::Ptr> getAll() = 0;

    /**
     * @param billID id of the bill
     * @return returns all items of a bill
     */
    virtual QList<BillItem::Ptr> getItemsOfBill(int billID) = 0;
};

#endif // BILLITEMDAO_H
