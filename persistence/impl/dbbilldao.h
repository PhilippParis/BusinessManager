#ifndef DBBILLDAO_H
#define DBBILLDAO_H

#include <QtSql>

#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/billdao.h"
#include "persistence/customerdao.h"

#include "domain/bill.h"

class DBBillDAO : public BillDAO
{
public:
    DBBillDAO(QSqlDatabase database, Validator<Bill::Ptr>::Ptr validator, CustomerDAO::Ptr customerDAO);

    Bill::Ptr get(int id) override;
    QList<Bill::Ptr> getAll() override;
    bool create(Bill::Ptr item) override;
    bool update(Bill::Ptr item) override;
    bool remove(Bill::Ptr item) override;

private:
    Bill::Ptr parseBill(QSqlRecord record);

private:
    QSqlDatabase m_database;
    Validator<Bill::Ptr>::Ptr m_validator;
    CustomerDAO::Ptr m_customerDAO;
};

#endif // DBBILLDAO_H
