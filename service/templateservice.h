#ifndef TEMPLATESERVICE_H
#define TEMPLATESERVICE_H

#include "memory"

#include "serviceexception.h"

class TemplateService
{
public:
    typedef std::shared_ptr<TemplateService> Ptr;

    TemplateService();
    ~TemplateService();
};

#endif // TEMPLATESERVICE_H
