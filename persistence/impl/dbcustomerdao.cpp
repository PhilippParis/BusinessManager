#include "dbcustomerdao.h"

DBCustomerDAO::DBCustomerDAO(QSqlDatabase database, Validator<Customer::Ptr>::Ptr validator)
 : m_database(database),
   m_validator(validator)
{

}

Customer::Ptr DBCustomerDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBCustomerDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM CUSTOMER WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving customer failed" + query.lastError().text();
        throw new PersistenceException("retrieving customer failed" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no customer with id'" + QString::number(id) + "' found";
        throw new PersistenceException("no customer with id'" + QString::number(id) + "' found");
    }

    return parseCustomer(query.record());
}

QList<Customer::Ptr> DBCustomerDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBCustomerDAO::getAll";

    QList<Customer::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM CUSTOMER WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving customers failed" + query.lastError().text();
        throw new PersistenceException("retrieving customer failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseCustomer(query.record()));
    }

    return items;
}

void DBCustomerDAO::create(Customer::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBCustomerDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO CUSTOMER VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, 0);");

    insertQuery.addBindValue(item->title());
    insertQuery.addBindValue(item->name());
    insertQuery.addBindValue(item->surname());
    insertQuery.addBindValue(item->organisation());
    insertQuery.addBindValue(item->mail());
    insertQuery.addBindValue(item->city());
    insertQuery.addBindValue(item->street());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBCustomerDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBCustomerDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());
}

void DBCustomerDAO::update(Customer::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBCustomerDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE CUSTOMER SET "
                        "TITLE = ?, "
                        "NAME = ?, "
                        "SURNAME = ?, "
                        "ORG = ?, "
                        "MAIL = ?, "
                        "CITY= ?, "
                        "STREET = ? "
                        "WHERE ID = ?;");

    updateQuery.addBindValue(item->title());
    updateQuery.addBindValue(item->name());
    updateQuery.addBindValue(item->surname());
    updateQuery.addBindValue(item->organisation());
    updateQuery.addBindValue(item->mail());
    updateQuery.addBindValue(item->city());
    updateQuery.addBindValue(item->street());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBCustomerDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBCustomerDAO::update failed:" + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBCustomerDAO::update dataset not found";
        throw new PersistenceException("DBCustomerDAO::update dataset not found");
    }
}

void DBCustomerDAO::remove(Customer::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBCustomerDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE CUSTOMER SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBCustomerDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBCustomerDAO::remove failed:" + removeQuery.lastError().text());
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBCustomerDAO::remove dataset not found";
        throw new PersistenceException("DBCustomerDAO::remove dataset not found");
    }
}

Customer::Ptr DBCustomerDAO::parseCustomer(QSqlRecord record)
{
    Customer::Ptr customer = std::make_shared<Customer>();

    customer->setId(record.value("ID").toInt());
    customer->setTitle(record.value("TITLE").toString());
    customer->setOrganisation(record.value("ORG").toString());
    customer->setName(record.value("NAME").toString());
    customer->setSurname(record.value("SURNAME").toString());
    customer->setCity(record.value("CITY").toString());
    customer->setStreet(record.value("STREET").toString());
    customer->setMail(record.value("MAIL").toString());

    return customer;
}

