#ifndef MATERIALSERVICE_H
#define MATERIALSERVICE_H

#include "serviceexception.h"
#include "domain/material.h"

#include "persistence/validation/validator.h"

class MaterialService
{
public:
    typedef std::shared_ptr<MaterialService> Ptr;

    MaterialService();

    /**
     * @brief adds the material to the underlying datsource
     * @param material material to add
     */
    virtual void add(Material::Ptr material) = 0;

    /**
     * @brief updates the material to the underlying datsource
     * @param material material to update
     */
    virtual void update(Material::Ptr material) = 0;

    /**
     * @brief removes the material from the underlying datasource
     * @param material to remove
     */
    virtual void remove(Material::Ptr material) = 0;

    /**
     * @param id id of the material
     * @return returns the material with the specified id
     */
    virtual Material::Ptr get(int id) = 0;

    /**
     * @return returns all materials
     */
    virtual QList<Material::Ptr> getAll() = 0;

    /**
     * @return returns the material validator
     */
    virtual Validator<Material::Ptr>::Ptr validator() = 0;
};

#endif // MATERIALSERVICE_H
