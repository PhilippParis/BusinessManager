#ifndef TEMPLATEDAO_H
#define TEMPLATEDAO_H

#include <memory>

#include "logging.h"

#include "domain/template.h"
#include "persistence/persistenceexception.h"
#include "persistence/validation/validator.h"

class TemplateDAO
{
public:
    typedef std::shared_ptr<TemplateDAO> Ptr;

    TemplateDAO();
    ~TemplateDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @return true if the data was written succesfully
     */
    virtual void create(Template::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @return true if the data was updated successfully
     */
    virtual void update(Template::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @return true if the data was removed successfully
     */
    virtual void remove(Template::Ptr item) = 0;

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist / an error occurred
     */
    virtual Template::Ptr get(int id) = 0;

    /**
     * @return returns all items from the underlying datasource
     */
    virtual QList<Template::Ptr> getAll() = 0;
};

#endif // TEMPLATEDAO_H
