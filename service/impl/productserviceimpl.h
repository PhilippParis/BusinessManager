#ifndef PRODUCTSERVICEIMPL_H
#define PRODUCTSERVICEIMPL_H

#include "service/productservice.h"

#include "persistence/productdao.h"
#include "persistence/validation/validator.h"

class ProductServiceImpl : public ProductService
{
public:
    ProductServiceImpl(ProductDAO::Ptr productDAO, Validator<Product::Ptr>::Ptr productValidator);

    void add(Product::Ptr product);
    void update(Product::Ptr product);
    void remove(Product::Ptr product);
    Product::Ptr get(int id);
    QList<Product::Ptr> getAll();

private:
    ProductDAO::Ptr m_productDAO;
    Validator<Product::Ptr>::Ptr m_productValidator;
};

#endif // PRODUCTSERVICEIMPL_H
