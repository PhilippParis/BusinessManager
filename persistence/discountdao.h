#ifndef DISCOUNTDAO_H
#define DISCOUNTDAO_H

#include "persistence/persistenceexception.h"

#include "domain/discount.h"

class DiscountDAO
{
public:
    typedef std::shared_ptr<DiscountDAO> Ptr;

    DiscountDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @throws PersistenceException if an error occurred
     */
    virtual void create(Discount::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @throws PersistenceException if an error occurred or the dataset
     *         to update was not found
     */
    virtual void update(Discount::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @throws PersistenceException if an error occurred or the dataset
     *         to remove was not found
     */
    virtual void remove(Discount::Ptr item) = 0;

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist / an error occurred
     */
    virtual Discount::Ptr get(int id) = 0;

    /**
     * @param billID id of the bill
     * @return returns all discounts of the specified bill
     */
    virtual QList<Discount::Ptr> getDiscountsOfBill(int billID) = 0;
};

#endif // DISCOUNTDAO_H
