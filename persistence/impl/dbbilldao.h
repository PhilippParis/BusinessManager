#ifndef DBBILLDAO_H
#define DBBILLDAO_H

#include <QtSql>

#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/billdao.h"
#include "persistence/customerdao.h"
#include "persistence/billitemdao.h"

#include "domain/bill.h"

class DBBillDAO : public BillDAO
{
public:
    DBBillDAO(QSqlDatabase database, Validator<Bill::Ptr>::Ptr validator, CustomerDAO::Ptr customerDAO, BillItemDAO::Ptr billItemDAO);

    Bill::Ptr get(int id) override;
    QList<Bill::Ptr> getAll() override;
    void create(Bill::Ptr item) override;
    void update(Bill::Ptr item) override;
    void remove(Bill::Ptr item) override;

    int nextBillNumber(QDate date) override;
    QPair<QDate, QDate> billDateRange() override;

private:
    Bill::Ptr parseBill(QSqlRecord record);
    void updateBillItems(Bill::Ptr item);

private:
    QSqlDatabase m_database;
    Validator<Bill::Ptr>::Ptr m_validator;
    CustomerDAO::Ptr m_customerDAO;
    BillItemDAO::Ptr m_billItemDAO;
};

#endif // DBBILLDAO_H
