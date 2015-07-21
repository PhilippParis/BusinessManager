#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <memory>

#include "validationexception.h"

template <typename T>
class Validator
{
public:
    typedef std::shared_ptr<Validator<T>> Ptr;

    virtual void validateForCreate(T item) = 0;
    virtual void validateForUpdate(T item) = 0;
    virtual void validateIdentity(T item) = 0;
};

#endif // VALIDATOR_H
