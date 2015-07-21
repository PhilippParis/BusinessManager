#ifndef SERVICEEXCEPTION_H
#define SERVICEEXCEPTION_H

#include "exception.h"

class ServiceException : public Exception
{
public:
    ServiceException(QString msg);
    ServiceException(Exception *e);
};

#endif // SERVICEEXCEPTION_H
