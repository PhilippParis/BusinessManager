#ifndef LETTERSERVICE_H
#define LETTERSERVICE_H

#include "domain/letter.h"
#include "persistence/validation/validator.h"

class LetterService
{
public:
    typedef std::shared_ptr<LetterService> Ptr;
    LetterService();

    virtual void add(Letter::Ptr offer) = 0;
    virtual void update(Letter::Ptr offer) = 0;
    virtual void remove(Letter::Ptr offer) = 0;
    virtual Letter::Ptr get(int id) = 0;
    virtual QList<Letter::Ptr> getAll() = 0;

    virtual Validator<Letter::Ptr>::Ptr validator() = 0;
};

#endif // LETTERSERVICE_H
