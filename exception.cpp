#include "exception.h"

Exception::Exception(Exception *e)
 : m_msg(e->what()),
   m_parent(e)
{

}

Exception::Exception(QString msg)
 : m_msg(msg)
{

}

Exception::~Exception()
{
    if(m_parent != nullptr) {
        delete m_parent;
    }
}

const char *Exception::what() const noexcept
{
    return m_msg.toStdString().c_str();
}

Exception *Exception::parent() const
{
    return m_parent;
}



