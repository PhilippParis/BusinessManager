#ifndef DBBILLITEMDAO_H
#define DBBILLITEMDAO_H

#include <QtSql>

#include "persistence/billitemdao.h"
#include "persistence/validation/validator.h"

class DBBillItemDAO : public BillItemDAO
{
public:
    DBBillItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator);
    ~DBBillItemDAO();

public:
    BillItem::Ptr get(int id) override;
    bool write(BillItem::Ptr item) override;
    bool update(BillItem::Ptr item) override;
    bool remove(BillItem::Ptr item) override;

private:
    BillItem::Ptr parseBillItem(QSqlRecord record);

private:
    QSqlDatabase m_database;
    Validator<BillItem::Ptr>::Ptr m_validator;
};

#endif // DBBILLITEMDAO_H
