#ifndef MATERIALSERVICEIMPL_H
#define MATERIALSERVICEIMPL_H

#include "service/materialservice.h"

#include "persistence/materialdao.h"
#include "persistence/validation/validator.h"

class MaterialServiceImpl : public MaterialService
{
public:
    MaterialServiceImpl(MaterialDAO::Ptr materialDAO, Validator<Material::Ptr>::Ptr materialValidator);

    void add(Material::Ptr material);
    void update(Material::Ptr material);
    void remove(Material::Ptr material);
    Material::Ptr get(int id);
    QList<Material::Ptr> getAll();

    Validator<Material::Ptr>::Ptr validator();

private:
    MaterialDAO::Ptr m_materialDAO;
    Validator<Material::Ptr>::Ptr m_materialValidator;
};

#endif // MATERIALSERVICEIMPL_H
