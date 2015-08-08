#include "dbbillitemdao.h"

DBBillItemDAO::DBBillItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator, MaterialDAO::Ptr materialDAO)
 : DBItemDAO(db, validator, materialDAO)
{
}

void DBBillItemDAO::create(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::create with param " + item->toString();

    DBItemDAO::create(item);

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO BILL_ITEM VALUES(?, NULL);");
    insertQuery.addBindValue(item->id());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillItemDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBBillItemDAO::create failed: " + insertQuery.lastError().text());
    }
}

void DBBillItemDAO::update(BillItem::Ptr item)
{
    DBItemDAO::update(item);
}

void DBBillItemDAO::remove(BillItem::Ptr item)
{
    DBItemDAO::remove(item);
}

BillItem::Ptr DBBillItemDAO::get(int id)
{
    return DBItemDAO::get(id);
}

QList<BillItem::Ptr> DBBillItemDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::getAll";

    QList<BillItem::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL_ITEM NATURAL JOIN ITEM WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving billItems failed" + query.lastError().text();
        throw new PersistenceException("retrieving billItems failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseItem(query.record()));
    }

    return items;
}

QList<BillItem::Ptr> DBBillItemDAO::getItemsOfBill(int billID)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::getItemsOfBill";

    QList<BillItem::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL_ITEM NATURAL JOIN ITEM WHERE DELETED = 0 AND BILL = ?");
    query.addBindValue(billID);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving billItems failed" + query.lastError().text();
        throw new PersistenceException("retrieving billItems failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseItem(query.record()));
    }

    return items;
}

