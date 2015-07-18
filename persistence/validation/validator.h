#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <memory>

template <typename T>
class Validator
{
public:
    typedef std::shared_ptr<Validator<T>> Ptr;

    virtual bool validateForCreate(T item) = 0;
    virtual bool validateForUpdate(T item) = 0;
    virtual bool validateIdentity(T item) = 0;
};

#endif // VALIDATOR_H
