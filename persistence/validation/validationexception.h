#ifndef VALIDATIONEXCEPTION_H
#define VALIDATIONEXCEPTION_H

#include "exception.h"

class ValidationException : public Exception
{
public:
    ValidationException(QString msg);
    ValidationException(Exception *e);
};

#endif // VALIDATIONEXCEPTION_H
