#ifndef DBBILLITEMDAO_H
#define DBBILLITEMDAO_H

#include <QtSql>

#include "decimal.h"
#include "logging.h"
#include "persistence/billitemdao.h"

#include "persistence/validation/validator.h"
#include "persistence/billdao.h"
#include "persistence/materialdao.h"

class DBBillItemDAO : public BillItemDAO
{
public:
    DBBillItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator, MaterialDAO::Ptr materialDAO);

public:
    BillItem::Ptr get(int id) override;
    QList<BillItem::Ptr> getAll() override;
    QList<BillItem::Ptr> getItemsOfBill(int billID) override;
    void create(BillItem::Ptr item) override;
    void update(BillItem::Ptr item) override;
    void remove(BillItem::Ptr item) override;

private:
    BillItem::Ptr parseBillItem(QSqlRecord record);
    void updateAssocTable(BillItem::Ptr item);

private:
    QSqlDatabase m_database;
    Validator<BillItem::Ptr>::Ptr m_validator;
    MaterialDAO::Ptr m_materialDAO;
};

#endif // DBBILLITEMDAO_H
