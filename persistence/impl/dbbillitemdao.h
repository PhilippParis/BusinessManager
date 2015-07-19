#ifndef DBBILLITEMDAO_H
#define DBBILLITEMDAO_H

#include <QtSql>

#include "logging.h"
#include "persistence/billitemdao.h"
#include "persistence/validation/validator.h"

class DBBillItemDAO : public BillItemDAO
{
public:
    DBBillItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator);

public:
    BillItem::Ptr get(int id) override;
    QList<BillItem::Ptr> getAll() override;
    bool create(BillItem::Ptr item) override;
    bool update(BillItem::Ptr item) override;
    bool remove(BillItem::Ptr item) override;

private:
    BillItem::Ptr parseBillItem(QSqlRecord record);

private:
    QSqlDatabase m_database;
    Validator<BillItem::Ptr>::Ptr m_validator;
};

#endif // DBBILLITEMDAO_H
