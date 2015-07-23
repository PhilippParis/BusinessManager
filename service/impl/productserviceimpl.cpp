#include "productserviceimpl.h"

ProductServiceImpl::ProductServiceImpl(ProductDAO::Ptr productDAO, Validator<Product::Ptr>::Ptr productValidator)
 : m_productDAO(productDAO),
   m_productValidator(productValidator)
{

}

void ProductServiceImpl::add(Product::Ptr product)
{
    try {
        m_productValidator->validateForCreate(product);
        m_productDAO->create(product);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void ProductServiceImpl::update(Product::Ptr product)
{
    try {
        m_productValidator->validateForUpdate(product);
        m_productDAO->update(product);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void ProductServiceImpl::remove(Product::Ptr product)
{
    try {
        m_productValidator->validateIdentity(product);
        m_productDAO->remove(product);
    } catch (Exception *e) {
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
