#ifndef TEMPLATESERVICEIMPL_H
#define TEMPLATESERVICEIMPL_H

#include "service/templateservice.h"

#include "persistence/templatedao.h"

class TemplateServiceImpl : public TemplateService
{
public:
    TemplateServiceImpl(TemplateDAO::Ptr templateDAO, Validator<Template::Ptr>::Ptr templateValidator);

    void add(Template::Ptr templ);
    void update(Template::Ptr templ);
    void remove(Template::Ptr templ);
    Template::Ptr get(int id);
    QList<Template::Ptr> getAll();

    Validator<Template::Ptr>::Ptr validator();
private:
    TemplateDAO::Ptr m_templateDAO;
    Validator<Template::Ptr>::Ptr m_templateValidator;
};

#endif // TEMPLATESERVICEIMPL_H
