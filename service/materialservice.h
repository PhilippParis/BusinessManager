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

    virtual void add(Material::Ptr material) = 0;
    virtual void update(Material::Ptr material) = 0;
    virtual void remove(Material::Ptr material) = 0;
    virtual Material::Ptr get(int id) = 0;
    virtual QList<Material::Ptr> getAll() = 0;

    virtual Validator<Material::Ptr>::Ptr validator() = 0;
};

#endif // MATERIALSERVICE_H
