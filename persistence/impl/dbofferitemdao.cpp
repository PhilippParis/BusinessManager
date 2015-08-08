#include "dbofferitemdao.h"

DBOfferItemDAO::DBOfferItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator, MaterialDAO::Ptr materialDAO)
 : DBItemDAO(db, validator, materialDAO)
{

}

void DBOfferItemDAO::create(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBOfferItemDAO::create with param " + item->toString();

    DBItemDAO::create(item);

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO OFFER_ITEM VALUES(?, NULL);");
    insertQuery.addBindValue(item->id());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBOfferItemDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBOfferItemDAO::create failed: " + insertQuery.lastError().text());
    }
}

void DBOfferItemDAO::update(BillItem::Ptr item)
{
    DBItemDAO::update(item);
}

void DBOfferItemDAO::remove(BillItem::Ptr item)
{
    DBItemDAO::remove(item);
}

BillItem::Ptr DBOfferItemDAO::get(int id)
{
    return DBItemDAO::get(id);
}

QList<BillItem::Ptr> DBOfferItemDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBOfferItemDAO::getAll";

    QList<BillItem::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM OFFER_ITEM NATURAL JOIN ITEM WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving offerItems failed" + query.lastError().text();
        throw new PersistenceException("retrieving offerItems failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseItem(query.record()));
    }

    return items;
}

QList<BillItem::Ptr> DBOfferItemDAO::getItemsOfOffer(int offerID)
{
    qCDebug(lcPersistence) << "Entering DBOfferItemDAO::getItemsOfBill";

    QList<BillItem::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM OFFER_ITEM NATURAL JOIN ITEM WHERE DELETED = 0 AND BILL = ?");
    query.addBindValue(offerID);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving offerItems failed" + query.lastError().text();
        throw new PersistenceException("retrieving offerItems failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseItem(query.record()));
    }

    return items;
}
