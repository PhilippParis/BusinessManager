#include "templateserviceimpl.h"

TemplateServiceImpl::TemplateServiceImpl(TemplateDAO::Ptr templateDAO, Validator<Template::Ptr>::Ptr templateValidator)
 : m_templateDAO(templateDAO),
   m_templateValidator(templateValidator)
{

}

void TemplateServiceImpl::add(Template::Ptr templ)
{
    try {
        m_templateValidator->validateForCreate(templ);
        m_templateDAO->create(templ);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void TemplateServiceImpl::update(Template::Ptr templ)
{
    try {
        m_templateValidator->validateForUpdate(templ);
        m_templateDAO->update(templ);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void TemplateServiceImpl::remove(Template::Ptr templ)
{
    try {
        m_templateValidator->validateIdentity(templ);
        m_templateDAO->remove(templ);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

Template::Ptr TemplateServiceImpl::get(int id)
{
    try {
        return m_templateDAO->get(id);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

QList<Template::Ptr> TemplateServiceImpl::getAll()
{
    try {
        return m_templateDAO->getAll();
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

Validator<Template::Ptr>::Ptr TemplateServiceImpl::validator()
{
    return m_templateValidator;
}

