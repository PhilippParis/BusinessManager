#ifndef LETTERDAO_H
#define LETTERDAO_H

#include "domain/letter.h"
#include "persistence/persistenceexception.h"

class LetterDAO
{
public:
    typedef std::shared_ptr<LetterDAO> Ptr;

    LetterDAO();

    /**
     * @brief writes \p item to the underlying data source
     * @param item item to write
     * @throws PersistenceException if an error occurred
     */
    virtual void create(Letter::Ptr item) = 0;

    /**
     * @brief updates the item data in the underlying data source
     * @param item data to update
     * @throws PersistenceException if an error occurred or the dataset
     *         to update was not found
     */
    virtual void update(Letter::Ptr item) = 0;

    /**
     * @brief removes the item from the underlying data source
     * @param item item to remove
     * @throws PersistenceException if an error occurred or the dataset
     *         to remove was not found
     */
    virtual void remove(Letter::Ptr item) = 0;

    /**
     * @param id id of the item to retrieve
     * @return returns a billitem from the underlying data source, or
     * null if the item does not exist / an error occurred
     */
    virtual Letter::Ptr get(int id) = 0;

    /**
     * @return returns all items from the underlying datasource
     */
    virtual QList<Letter::Ptr> getAll() = 0;
};

#endif // LETTERDAO_H
