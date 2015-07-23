#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H

#include "serviceexception.h"
#include "domain/product.h"

class ProductService
{
public:
    typedef std::shared_ptr<ProductService> Ptr;

    ProductService();

    virtual void add(Product::Ptr product) = 0;
    virtual void update(Product::Ptr product) = 0;
    virtual void remove(Product::Ptr product) = 0;
    virtual Product::Ptr get(int id) = 0;
    virtual QList<Product::Ptr> getAll() = 0;
};

#endif // PRODUCTSERVICE_H
