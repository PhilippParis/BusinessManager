#include "customerserviceimpl.h"

CustomerServiceImpl::CustomerServiceImpl(CustomerDAO::Ptr customerDAO, Validator<Customer::Ptr>::Ptr customerValidator)
 : m_customerDAO(customerDAO),
   m_customerValidator(customerValidator)
{

}

void CustomerServiceImpl::add(Customer::Ptr customer)
{
    try {
        m_customerValidator->validateForCreate(customer);
        m_customerDAO->create(customer);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void CustomerServiceImpl::update(Customer::Ptr customer)
{
    try {
        m_customerValidator->validateForUpdate(customer);
        m_customerDAO->update(customer);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void CustomerServiceImpl::remove(Customer::Ptr customer)
{
    try {
        m_customerValidator->validateIdentity(customer);
        m_customerDAO->remove(customer);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

Customer::Ptr CustomerServiceImpl::get(int id)
{
    try {
        return m_customerDAO->get(id);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

QList<Customer::Ptr> CustomerServiceImpl::getAll()
{
    try {
        return m_customerDAO->getAll();
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}


