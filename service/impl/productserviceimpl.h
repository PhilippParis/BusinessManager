#ifndef PRODUCTSERVICEIMPL_H
#define PRODUCTSERVICEIMPL_H

#include "service/productservice.h"

#include "persistence/productdao.h"
#include "persistence/validation/validator.h"

class ProductServiceImpl : public ProductService
{
public:
    ProductServiceImpl(ProductDAO::Ptr productDAO, Validator<Product::Ptr>::Ptr productValidator);

    virtual void add(Product::Ptr product) = 0;
    virtual void update(Product::Ptr product) = 0;
    virtual void remove(Product::Ptr product) = 0;
    virtual Product::Ptr get(int id) = 0;
    virtual QList<Product::Ptr> getAll() = 0;

private:
    ProductDAO::Ptr m_productDAO;
    Validator<Product::Ptr>::Ptr m_productValidator;
};

#endif // PRODUCTSERVICEIMPL_H
