#include "letterserviceimpl.h"

LetterServiceImpl::LetterServiceImpl(LetterDAO::Ptr letterDAO, Validator<Letter::Ptr>::Ptr validator)
 : m_letterDAO(letterDAO),
   m_validator(validator)
{

}

void LetterServiceImpl::add(Letter::Ptr letter)
{
    try {
        m_validator->validateForCreate(letter);
        m_letterDAO->create(letter);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void LetterServiceImpl::update(Letter::Ptr letter)
{
    try {
        m_validator->validateForUpdate(letter);
        m_letterDAO->update(letter);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void LetterServiceImpl::remove(Letter::Ptr letter)
{
    try {
        m_validator->validateIdentity(letter);
        m_letterDAO->remove(letter);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

Letter::Ptr LetterServiceImpl::get(int id)
{
    try {
        return m_letterDAO->get(id);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

QList<Letter::Ptr> LetterServiceImpl::getAll()
{
    try {
        return m_letterDAO->getAll();
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

Validator<Letter::Ptr>::Ptr LetterServiceImpl::validator()
{
    return m_validator;
}


