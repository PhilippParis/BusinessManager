#ifndef TEMPLATEDAO_H
#define TEMPLATEDAO_H

#include <memory>

#include "persistence/persistenceexception.h"

class TemplateDAO
{
public:
    typedef std::shared_ptr<TemplateDAO> Ptr;

    TemplateDAO();
    ~TemplateDAO();
};

#endif // TEMPLATEDAO_H
