#include "serviceexception.h"

ServiceException::ServiceException(QString msg)
 : Exception(msg)
{

}

ServiceException::ServiceException(Exception *e)
 : Exception(e)
{

}
