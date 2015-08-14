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

    /**
     * @brief adds the template to the underlying datasource
     * @param templ template to add
     */
    virtual void add(Template::Ptr templ) = 0;

    /**
     * @brief updates the template in the underlying datasource
     * @param templ template to update
     */
    virtual void update(Template::Ptr templ) = 0;

    /**
     * @brief removes the template from the underlying datasource
     * @param templ template to remove
     */
    virtual void remove(Template::Ptr templ) = 0;

    /**
     * @param id id of the template
     * @return returns the template with the specified id
     */
    virtual Template::Ptr get(int id) = 0;

    /**
     * @return returns all templates
     */
    virtual QList<Template::Ptr> getAll() = 0;

    /**
     * @return returns the template validator
     */
    virtual Validator<Template::Ptr>::Ptr validator() = 0;
};

#endif // TEMPLATESERVICE_H
