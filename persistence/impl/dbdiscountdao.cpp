#include "dbdiscountdao.h"

DBDiscountDAO::DBDiscountDAO(QSqlDatabase database, Validator<Discount::Ptr>::Ptr validator)
 : m_database(database),
   m_validator(validator)
{

}

void DBDiscountDAO::create(Discount::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBDiscountDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO DISCOUNT VALUES(NULL, ?, ?, NULL, 0);");

    insertQuery.addBindValue(item->text());
    insertQuery.addBindValue(item->value());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBDiscountDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBDiscountDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());
}

void DBDiscountDAO::update(Discount::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBDiscountDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE DISCOUNT SET "
                        "TEXT = ?, "
                        "VALUE = ? "
                        "WHERE ID = ?;");

    updateQuery.addBindValue(item->text());
    updateQuery.addBindValue(item->value());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBDiscountDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBDiscountDAO::update failed:" + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBDiscountDAO::update dataset not found";
        throw new PersistenceException("DBDiscountDAO::update dataset not found");
    }
}

void DBDiscountDAO::remove(Discount::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBDiscountDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE DISCOUNT SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBDiscountDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBDiscountDAO::remove failed:" + removeQuery.lastError().text());
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBDiscountDAO::remove dataset not found";
        throw new PersistenceException("DBDiscountDAO::remove dataset not found");
    }
}

Discount::Ptr DBDiscountDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBDiscountDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM DISCOUNT WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBDiscountDAO::get failed:" + query.lastError().text();
        throw new PersistenceException("DBDiscountDAO::get failed:" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "DBDiscountDAO::get dataset not found";
        throw new PersistenceException("DBDiscountDAO::get dataset not found");
    }

    return parseDiscount(query.record());
}

QList<Discount::Ptr> DBDiscountDAO::getDiscountsOfBill(int billID)
{
    qCDebug(lcPersistence) << "Entering DBDiscountDAO::getDiscountsOfBill with id " + QString::number(billID);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM DISCOUNT WHERE BILL = ?");
    query.addBindValue(billID);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBDiscountDAO::getDiscountsOfBill failed:" + query.lastError().text();
        throw new PersistenceException("DBDiscountDAO::getDiscountsOfBill failed:" + query.lastError().text());
    }

    QList<Discount::Ptr> items;
    while (query.next()) {
        items.append(parseDiscount(query.record()));
    }

    return items;
}

Discount::Ptr DBDiscountDAO::parseDiscount(QSqlRecord record)
{
    Discount::Ptr discount = std::make_shared<Discount>();
    discount->setText(record.value("TEXT").toString());
    discount->setValue(record.value("VALUE").toDouble());
    discount->setId(record.value("ID").toInt());

    return discount;
}

