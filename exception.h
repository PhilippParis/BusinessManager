#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <QString>

class Exception : public std::exception
{
public:
    Exception(Exception *e);
    Exception(QString msg);
    ~Exception();

    const char* what() const noexcept override;
    Exception *parent() const;

private:
    QString m_msg;
    Exception *m_parent = nullptr;
};

#endif // EXCEPTION_H
