#ifndef TEMPLATESERVICE_H
#define TEMPLATESERVICE_H

#include "memory"

#include "serviceexception.h"
#include "domain/template.h"

#include "persistence/validation/validator.h"
class TemplateService
{
public:
    typedef std::shared_ptr<TemplateService> Ptr;

    TemplateService();

    virtual void add(Template::Ptr templ) = 0;
    virtual void update(Template::Ptr templ) = 0;
    virtual void remove(Template::Ptr templ) = 0;
    virtual Template::Ptr get(int id) = 0;
    virtual QList<Template::Ptr> getAll() = 0;

    virtual Validator<Template::Ptr>::Ptr validator() = 0;
};

#endif // TEMPLATESERVICE_H
