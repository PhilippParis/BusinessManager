#include "validationexception.h"

ValidationException::ValidationException(QString msg)
 : Exception(msg)
{

}

ValidationException::ValidationException(Exception *e)
 : Exception(e)
{

}
