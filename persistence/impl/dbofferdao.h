#ifndef DBOFFERDAO_H
#define DBOFFERDAO_H

#include <QtSql>

#include "persistence/offerdao.h"
#include "persistence/offeritemdao.h"
#include "persistence/customerdao.h"

class DBOfferDAO : public OfferDAO
{
public:
    DBOfferDAO(QSqlDatabase database, Validator<Offer::Ptr>::Ptr validator,
               OfferItemDAO::Ptr offerItemDAO, CustomerDAO::Ptr customerDAO);

    void create(Offer::Ptr item) override;
    void update(Offer::Ptr item) override;
    void remove(Offer::Ptr item) override;

    Offer::Ptr get(int id) override;
    QList<Offer::Ptr> getAll() override;

private:
    void updateOfferItems(Offer::Ptr offer);
    Offer::Ptr parseOffer(QSqlRecord record);

private:
    QSqlDatabase m_database;
    Validator<Offer::Ptr>::Ptr m_validator;
    OfferItemDAO::Ptr m_offerItemDAO;
    CustomerDAO::Ptr m_customerDAO;
};

#endif // DBOFFERDAO_H
