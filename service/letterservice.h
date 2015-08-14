#ifndef LETTERSERVICE_H
#define LETTERSERVICE_H

#include "domain/letter.h"
#include "persistence/validation/validator.h"

class LetterService
{
public:
    typedef std::shared_ptr<LetterService> Ptr;
    LetterService();

    /**
     * @brief adds the letter to the underlying datsource
     * @param letter letter to add
     */
    virtual void add(Letter::Ptr letter) = 0;

    /**
     * @brief updates the letter in the underlying datasource
     * @param letter letter to update
     */
    virtual void update(Letter::Ptr letter) = 0;

    /**
     * @brief removes the letter from the underlying datasource
     * @param letter letter to remove
     */
    virtual void remove(Letter::Ptr letter) = 0;

    /**
     * @param id id of the letter
     * @return returns the letter with the specified id
     */
    virtual Letter::Ptr get(int id) = 0;

    /**
     * @return returns all letters
     */
    virtual QList<Letter::Ptr> getAll() = 0;

    /**
     * @return returns the letter validator
     */
    virtual Validator<Letter::Ptr>::Ptr validator() = 0;
};

#endif // LETTERSERVICE_H
