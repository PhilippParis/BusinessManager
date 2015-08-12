#ifndef DBHTMLFILELETTERDAO_H
#define DBHTMLFILELETTERDAO_H

#include <QtSql>

#include "logging.h"
#include "persistence/persistenceexception.h"

#include "persistence/letterdao.h"
#include "persistence/validation/validator.h"
#include "persistence/customerdao.h"

class DBHTMLFileLetterDAO : public LetterDAO
{
public:
    DBHTMLFileLetterDAO(QSqlDatabase database, Validator<Letter::Ptr>::Ptr validator, CustomerDAO::Ptr customerDAO);

    void create(Letter::Ptr item) override;
    void update(Letter::Ptr item) override;
    void remove(Letter::Ptr item) override;

    Letter::Ptr get(int id) override;
    QList<Letter::Ptr> getAll() override;

private:
    Letter::Ptr parseLetter(QSqlRecord record);
    QString createHtmlFile(Letter::Ptr letter);
    void updateHtmlFile(Letter::Ptr letter);
    void removeHtmlFile(Letter::Ptr letter);

private:
    QSqlDatabase m_database;
    Validator<Letter::Ptr>::Ptr m_validator;
    CustomerDAO::Ptr m_customerDAO;
};

#endif // DBHTMLFILELETTERDAO_H
