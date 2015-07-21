#ifndef PERSISTENCEEXCEPTION_H
#define PERSISTENCEEXCEPTION_H

#include "exception.h"

class PersistenceException : public Exception
{
public:
    PersistenceException(QString msg);
    PersistenceException(Exception *e);
};

#endif // PERSISTENCEEXCEPTION_H
