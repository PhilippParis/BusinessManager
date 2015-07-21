#include "productserviceimpl.h"

ProductServiceImpl::ProductServiceImpl(ProductDAO::Ptr productDAO, Validator<Product::Ptr>::Ptr productValidator)
 : m_productDAO(productDAO),
   m_productValidator(productValidator)
{

}

void ProductServiceImpl::add(Product::Ptr product)
{
    m_productValidator->validateForCreate(product);

    try {
        m_productDAO->create(product);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

void ProductServiceImpl::update(Product::Ptr product)
{
    m_productValidator->validateForUpdate(product);

    try {
        m_productDAO->update(product);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

void ProductServiceImpl::remove(Product::Ptr product)
{
    m_productValidator->validateIdentity(product);

    try {
        m_productDAO->remove(product);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

Product::Ptr ProductServiceImpl::get(int id)
{
    try {
        return m_productDAO->get(id);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

QList<Product::Ptr> ProductServiceImpl::getAll()
{
    try {
        return m_productDAO->getAll();
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}
