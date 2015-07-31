#include "materialserviceimpl.h"

MaterialServiceImpl::MaterialServiceImpl(MaterialDAO::Ptr materialDAO, Validator<Material::Ptr>::Ptr materialValidator)
 : m_materialDAO(materialDAO),
   m_materialValidator(materialValidator)
{

}

void MaterialServiceImpl::add(Material::Ptr material)
{
    try {
        m_materialValidator->validateForCreate(material);
        m_materialDAO->create(material);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void MaterialServiceImpl::update(Material::Ptr material)
{
    try {
        m_materialValidator->validateForUpdate(material);
        m_materialDAO->update(material);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void MaterialServiceImpl::remove(Material::Ptr material)
{
    try {
        m_materialValidator->validateIdentity(material);
        m_materialDAO->remove(material);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

Material::Ptr MaterialServiceImpl::get(int id)
{
    try {
        return m_materialDAO->get(id);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

QList<Material::Ptr> MaterialServiceImpl::getAll()
{
    try {
        return m_materialDAO->getAll();
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

Validator<Material::Ptr>::Ptr MaterialServiceImpl::validator()
{
    return m_materialValidator;
}
