#ifndef MATERIALDAO_H
#define MATERIALDAO_H

#include <QList>

#include "domain/material.h"
#include "persistence/persistenceexception.h"

class MaterialDAO
{
public:
    typedef std::shared_ptr<MaterialDAO> Ptr;

    MaterialDAO();
    ~MaterialDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @return true if the data was written succesfully
     */
    virtual void create(Material::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @return true if the data was updated successfully
     */
    virtual void update(Material::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @return true if the data was removed successfully
     */
    virtual void remove(Material::Ptr item) = 0;

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist / an error occurred
     */
    virtual Material::Ptr get(int id) = 0;

    /**
     * @return returns all items from the underlying datasource
     */
    virtual QList<Material::Ptr> getAll() = 0;
};

#endif // MATERIALDAO_H
