#ifndef BILLDAO_H
#define BILLDAO_H

#include "domain/bill.h"
#include "persistence/persistenceexception.h"

class BillDAO
{
public:
    typedef std::shared_ptr<BillDAO> Ptr;

    BillDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @return true if the data was written succesfully
     */
    virtual void create(Bill::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @return true if the data was updated successfully
     */
    virtual void update(Bill::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @return true if the data was removed successfully
     */
    virtual void remove(Bill::Ptr item) = 0;

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist / an error occurred
     */
    virtual Bill::Ptr get(int id) = 0;

    /**
     * @param from start date
     * @param to end date
     * @return returns bills between from and to
     */
    virtual QList<Bill::Ptr> get(QDate from, QDate to) = 0;

    /**
     * @return returns all items from the underlying datasource
     */
    virtual QList<Bill::Ptr> getAll() = 0;

    /**
     * @param date date of the bill
     * @return returns the next bill number
     */
    virtual int nextBillNumber(QDate date) = 0;

    /**
     * @return returns the date of the first and the last bill
     */
    virtual QPair<QDate, QDate> billDateRange() = 0;
};

#endif // BILLDAO_H
