#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include "serviceexception.h"
#include "domain/customer.h"

class CustomerService
{
public:
    typedef std::shared_ptr<CustomerService> Ptr;
    CustomerService();

    /**
     * @brief adds the customer to the underlying datasource
     * @param customer customer to add
     */
    virtual void add(Customer::Ptr customer) = 0;

    /**
     * @brief update updates the customer in the underlying datasource
     * @param customer customer to update
     */
    virtual void update(Customer::Ptr customer) = 0;

    /**
     * @brief removes the customer from the underlying datasource
     * @param customer customer to remove
     */
    virtual void remove(Customer::Ptr customer) = 0;

    /**
     * @param id id of the customer
     * @return returns the customer with the specified id
     */
    virtual Customer::Ptr get(int id) = 0;

    /**
     * @return returns all customers from the underlying datasource
     */
    virtual QList<Customer::Ptr> getAll() = 0;
};

#endif // CUSTOMERSERVICE_H
