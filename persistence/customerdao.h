#ifndef CUSTOMERDAO_H
#define CUSTOMERDAO_H

#include "domain/customer.h"
#include "persistence/persistenceexception.h"

class CustomerDAO
{
public:
    typedef std::shared_ptr<CustomerDAO> Ptr;

    CustomerDAO();
    ~CustomerDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @throws PersistenceException if an error occurred
     */
    virtual void create(Customer::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @throws PersistenceException if an error occurred or the dataset
     *         to update was not found
     */
    virtual void update(Customer::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @throws PersistenceException if an error occurred or the dataset
     *         to remove was not found
     */
    virtual void remove(Customer::Ptr item) = 0;

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist / an error occurred
     */
    virtual Customer::Ptr get(int id) = 0;

    /**
     * @return returns all items from the underlying datasource
     */
    virtual QList<Customer::Ptr> getAll() = 0;
};

#endif // CUSTOMERDAO_H
