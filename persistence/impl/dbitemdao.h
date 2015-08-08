#ifndef DBITEMDAO_H
#define DBITEMDAO_H

#include <QtSql>

#include <persistence/billitemdao.h>
#include <persistence/itemdao.h>
#include <persistence/materialdao.h>
#include <persistence/validation/validator.h>

class DBItemDAO : public ItemDAO
{
public:
    DBItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator, MaterialDAO::Ptr materialDAO);
    BillItem::Ptr get(int id) override;
    QList<BillItem::Ptr> getAll() override;
    void create(BillItem::Ptr item) override;
    void update(BillItem::Ptr item) override;
    void remove(BillItem::Ptr item) override;

protected:
    BillItem::Ptr parseItem(QSqlRecord record);
    void updateAssocTable(BillItem::Ptr item);

protected:
    QSqlDatabase m_database;
    Validator<BillItem::Ptr>::Ptr m_validator;
    MaterialDAO::Ptr m_materialDAO;
};

#endif // DBITEMDAO_H
