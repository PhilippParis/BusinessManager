#ifndef LETTERSERVICEIMPL_H
#define LETTERSERVICEIMPL_H

#include "service/letterservice.h"
#include "persistence/letterdao.h"

#include "service/serviceexception.h"

class LetterServiceImpl : public LetterService
{
public:
    LetterServiceImpl(LetterDAO::Ptr letterDAO, Validator<Letter::Ptr>::Ptr validator);

    void add(Letter::Ptr customer) override;
    void update(Letter::Ptr customer) override;
    void remove(Letter::Ptr customer) override;
    Letter::Ptr get(int id) override;
    QList<Letter::Ptr> getAll() override;

    Validator<Letter::Ptr>::Ptr validator() override;

private:
    LetterDAO::Ptr m_letterDAO;
    Validator<Letter::Ptr>::Ptr m_validator;
};

#endif // LETTERSERVICEIMPL_H
