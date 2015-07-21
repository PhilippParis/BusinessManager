#include "persistenceexception.h"

PersistenceException::PersistenceException(QString msg)
 : Exception(msg)
{

}

PersistenceException::PersistenceException(Exception *e)
 : Exception(e)
{

}
