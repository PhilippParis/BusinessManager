#ifndef CUSTOMERSERVICEIMPL_H
#define CUSTOMERSERVICEIMPL_H

#include <QList>

#include "service/customerservice.h"

#include "persistence/customerdao.h"
#include "persistence/validation/validator.h"

class CustomerServiceImpl : public CustomerService
{
public:
    CustomerServiceImpl(CustomerDAO::Ptr customerDAO, Validator<Customer::Ptr>::Ptr customerValidator);

    void add(Customer::Ptr customer) override;
    void update(Customer::Ptr customer) override;
    void remove(Customer::Ptr customer) override;
    Customer::Ptr get(int id) override;
    QList<Customer::Ptr> getAll() override;

private:
    CustomerDAO::Ptr m_customerDAO;
    Validator<Customer::Ptr>::Ptr m_customerValidator;
};

#endif // CUSTOMERSERVICEIMPL_H
