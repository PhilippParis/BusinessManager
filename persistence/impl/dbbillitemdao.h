#ifndef DBBILLITEMDAO_H
#define DBBILLITEMDAO_H

#include <QtSql>

#include "persistence/billitemdao.h"

class DBBillItemDAO : public BillItemDAO
{
public:
    DBBillItemDAO(QSqlDatabase db);
    ~DBBillItemDAO();

private:
    BillItem::Ptr getFromDataSource(int id);
    bool writeToDataSource(BillItem::Ptr item, int billID);
    bool updateInDataSource(BillItem::Ptr item);
    bool removeFromDataSource(BillItem::Ptr item);

    BillItem::Ptr parseBillItem(QSqlRecord record);

private:
    QSqlDatabase m_database;
    QSqlQuery m_insertQuery;
    QSqlQuery m_updateQuery;
    QSqlQuery m_removeQuery;
};

#endif // DBBILLITEMDAO_H
