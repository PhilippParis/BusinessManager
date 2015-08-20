#include "dbofferdao.h"

DBOfferDAO::DBOfferDAO(QSqlDatabase database, Validator<Offer::Ptr>::Ptr validator, OfferItemDAO::Ptr offerItemDAO, CustomerDAO::Ptr customerDAO)
 : m_database(database),
   m_validator(validator),
   m_offerItemDAO(offerItemDAO),
   m_customerDAO(customerDAO)
{

}

void DBOfferDAO::create(Offer::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBOfferDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO OFFER VALUES(NULL, ?, ?, 0);");

    insertQuery.addBindValue(item->date().toString("yyyy-MM-dd"));
    insertQuery.addBindValue(item->customer()->id());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBOfferDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBOfferDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());
    updateOfferItems(item);
}

void DBOfferDAO::update(Offer::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBOfferDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE OFFER SET "
                        "DATE = ?, "
                        "CUSTOMER = ? "
                        "WHERE ID = ?;");

    updateQuery.addBindValue(item->date().toString("yyyy-MM-dd"));
    updateQuery.addBindValue(item->customer()->id());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBOfferDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBOfferDAO::update failed: " + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBOfferDAO::update failed: dataset not found";
        throw new PersistenceException("DBOfferDAO::update failed: dataset not found");
    }

    updateOfferItems(item);
}

void DBOfferDAO::remove(Offer::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBOfferDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE OFFER SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBOfferDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBOfferDAO::remove failed:" + removeQuery.lastError().text());
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBOfferDAO::remove failed: dataset not found";
        throw new PersistenceException("DBOfferDAO::remove failed: dataset not found");
    }
}

Offer::Ptr DBOfferDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBOfferDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM OFFER WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving offer failed" + query.lastError().text();
        throw new PersistenceException("retrieving offer failed" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no offer with id'" + QString::number(id) + "' found";
        throw new PersistenceException("no offer with id'" + QString::number(id) + "' found");
    }

    return parseOffer(query.record());
}

QList<Offer::Ptr> DBOfferDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBOfferDAO::getAll";

    QList<Offer::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM OFFER WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving offers failed" + query.lastError().text();
        throw new PersistenceException("retrieving offers failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseOffer(query.record()));
    }

    return items;
}

void DBOfferDAO::updateOfferItems(Offer::Ptr offer)
{
    qCDebug(lcPersistence) << "Entering DBOfferDAO::updateOfferItems with param " + offer->toString();
    QList<BillItem::Ptr> items = offer->items();

    // set all already stored items as deleted
    QSqlQuery query(m_database);
    query.prepare("UPDATE ITEM SET DELETED = 1 WHERE ID IN (SELECT ID FROM OFFER_ITEM WHERE OFFER = ?);");
    query.addBindValue(offer->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBOfferDAO::updateOfferItems failed:" + query.lastError().text();
        throw new PersistenceException("DBOfferDAO::updateOfferItems failed:" + query.lastError().text());
    }

    QStringList placeholders;
    for (int i = 0; i < items.size(); ++i) {
         placeholders << "?";
    }

    // enable items
    query.prepare("UPDATE ITEM SET DELETED = 0 WHERE ID IN (" + placeholders.join(", ") + ")");
    for (int i = 0; i < items.size(); ++i) {
         query.addBindValue(items.at(i)->id());
    }
    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBOfferDAO::updateOfferItems failed:" + query.lastError().text();
        throw new PersistenceException("DBOfferDAO::updateOfferItems failed:" + query.lastError().text());
    }

    // set offer id
    query.prepare("UPDATE OFFER_ITEM SET OFFER = ? WHERE ID IN (" + placeholders.join(", ") + ")");
    query.addBindValue(offer->id());
    for (int i = 0; i < items.size(); ++i) {
         query.addBindValue(items.at(i)->id());
    }

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBOfferDAO::updateOfferItems failed:" + query.lastError().text();
        throw new PersistenceException("DBOfferDAO::updateOfferItems failed:" + query.lastError().text());
    }
}

Offer::Ptr DBOfferDAO::parseOffer(QSqlRecord record)
{
    Offer::Ptr offer = std::make_shared<Offer>();

    offer->setId(record.value("ID").toInt());
    offer->setDate(QDate::fromString(record.value("DATE").toString(), "yyyy-MM-dd"));
    offer->setCustomer(m_customerDAO->get(record.value("CUSTOMER").toInt()));

    // get items
    QSqlQuery query(m_database);
    query.prepare("SELECT ID FROM OFFER_ITEM NATURAL JOIN ITEM WHERE OFFER = ? AND DELETED = 0;");
    query.addBindValue(offer->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBOfferDAO::parseOffer failed:" + query.lastError().text();
        throw new PersistenceException("DBOfferDAO::parseOffer failed:" + query.lastError().text());
    }

    QList<BillItem::Ptr> items;
    while(query.next()) {
        items.append(m_offerItemDAO->get(query.value("ID").toInt()));
    }
    offer->setItems(items);

    return offer;
}

