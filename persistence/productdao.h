#ifndef PRODUCTDAO_H
#define PRODUCTDAO_H

#include <QList>

#include "domain/product.h"
#include "persistence/persistenceexception.h"

class ProductDAO
{
public:
    typedef std::shared_ptr<ProductDAO> Ptr;

    ProductDAO();
    ~ProductDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @return true if the data was written succesfully
     */
    virtual void create(Product::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @return true if the data was updated successfully
     */
    virtual void update(Product::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @return true if the data was removed successfully
     */
    virtual void remove(Product::Ptr item) = 0;

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist / an error occurred
     */
    virtual Product::Ptr get(int id) = 0;

    /**
     * @return returns all items from the underlying datasource
     */
    virtual QList<Product::Ptr> getAll() = 0;
};

#endif // PRODUCTDAO_H
