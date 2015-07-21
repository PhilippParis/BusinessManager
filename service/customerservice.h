#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include "serviceexception.h"
#include "domain/customer.h"

class CustomerService
{
public:
    CustomerService();

    virtual void add(Customer::Ptr) = 0;
    virtual void update(Customer::Ptr) = 0;
    virtual void remove(Customer::Ptr) = 0;
    virtual Customer::Ptr get(int id) = 0;
    virtual QList<Customer::Ptr> getAll() = 0;
};

#endif // CUSTOMERSERVICE_H
