#ifndef CUSTOMERDAO_H
#define CUSTOMERDAO_H

#include "domain/customer.h"

class CustomerDAO
{
public:
    typedef std::shared_ptr<CustomerDAO> Ptr;

    CustomerDAO();
    ~CustomerDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @return true if the data was written succesfully
     */
    virtual bool create(Customer::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @return true if the data was updated successfully
     */
    virtual bool update(Customer::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @return true if the data was removed successfully
     */
    virtual bool remove(Customer::Ptr item) = 0;

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
