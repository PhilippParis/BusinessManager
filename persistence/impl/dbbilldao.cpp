#include "dbbilldao.h"

DBBillDAO::DBBillDAO(QSqlDatabase database, Validator<Bill::Ptr>::Ptr validator, CustomerDAO::Ptr customerDAO)
 : m_database(database),
   m_validator(validator),
   m_customerDAO(customerDAO)
{
}

Bill::Ptr DBBillDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving bill failed" + query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no bill with id'" + QString::number(id) + "' found";
        return nullptr;
    }

    return parseBill(query.record());
}

QList<Bill::Ptr> DBBillDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::getAll";

    QList<Bill::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving bills failed" + query.lastError().text();
        return items;
    }

    while(query.next()) {
        items.append(parseBill(query.record()));
    }

    return items;
}

bool DBBillDAO::create(Bill::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::create with param " + item->toString();

    if (!m_validator->validateForCreate(item)) {
        return false;
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO BILL VALUES(NULL, ?, ?, ?, ?, 0);");

    insertQuery.addBindValue(item->billNumber());
    insertQuery.addBindValue(item->date().toJulianDay());
    insertQuery.addBindValue(item->payed());
    insertQuery.addBindValue(item->customer()->id());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::create failed: " + insertQuery.lastError().text();
        return false;
    }

    item->setId(insertQuery.lastInsertId().toInt());
    return true;
}

bool DBBillDAO::update(Bill::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::update with param " + item->toString();

    if (!m_validator->validateForUpdate(item)) {
        return false;
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE BILL SET "
                        "NR = ?, "
                        "DATE = ?, "
                        "PAYED = ?, "
                        "CUSTOMER = ? "
                        "WHERE ID = ?;");

    updateQuery.addBindValue(item->billNumber());
    updateQuery.addBindValue(item->date().toJulianDay());
    updateQuery.addBindValue(item->payed());
    updateQuery.addBindValue(item->customer()->id());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::update failed:" + updateQuery.lastError().text();
        return false;
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBBillDAO::update failed: dataset not found";
        return false;
    }

    return true;
}

bool DBBillDAO::remove(Bill::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::remove with param " + item->toString();

    if (!m_validator->validateIdentity(item)) {
        return false;
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE BILL SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::remove failed:" + removeQuery.lastError().text();
        return false;
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBBillDAO::remove failed: dataset not found";
        return false;
    }

    return true;
}

Bill::Ptr DBBillDAO::parseBill(QSqlRecord record)
{
    Bill::Ptr bill = std::make_shared<Bill>();

    bill->setId(record.value("ID").toInt());
    bill->setBillNumber(record.value("NR").toInt());
    bill->setPayed(record.value("PAYED").toBool());
    bill->setDate(QDate::fromJulianDay(record.value("DATE").toDouble()));
    bill->setCustomer(m_customerDAO->get(record.value("CUSTOMER").toInt()));

    return bill;
}


