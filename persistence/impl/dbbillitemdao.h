#ifndef DBBILLITEMDAO_H
#define DBBILLITEMDAO_H

#include <QtSql>

#include "decimal.h"
#include "logging.h"
#include "persistence/billitemdao.h"

#include "persistence/validation/validator.h"
#include "persistence/impl/dbitemdao.h"
#include "persistence/billdao.h"
#include "persistence/materialdao.h"

class DBBillItemDAO : public DBItemDAO, public BillItemDAO
{
public:
    DBBillItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator, MaterialDAO::Ptr materialDAO);

    void create(BillItem::Ptr item) override;
    void update(BillItem::Ptr item) override;
    void remove(BillItem::Ptr item) override;
    BillItem::Ptr get(int id) override;
    QList<BillItem::Ptr> getAll() override;
    QList<BillItem::Ptr> getItemsOfBill(int billID) override;
};

#endif // DBBILLITEMDAO_H
