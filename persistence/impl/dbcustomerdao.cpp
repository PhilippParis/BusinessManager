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
        return nullptr;
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no customer with id'" + QString::number(id) + "' found";
        return nullptr;
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
        return items;
    }

    while(query.next()) {
        items.append(parseCustomer(query.record()));
    }

    return items;
}

bool DBCustomerDAO::create(Customer::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBCustomerDAO::create with param " + item->toString();

    if (!m_validator->validateForCreate(item)) {
        return false;
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
        return false;
    }

    item->setId(insertQuery.lastInsertId().toInt());
    return true;
}

bool DBCustomerDAO::update(Customer::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBCustomerDAO::update with param " + item->toString();

    if (!m_validator->validateForUpdate(item)) {
        return false;
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
        return false;
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBCustomerDAO::update dataset not found";
        return false;
    }

    return true;
}

bool DBCustomerDAO::remove(Customer::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBCustomerDAO::remove with param " + item->toString();

    if (!m_validator->validateIdentity(item)) {
        return false;
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE CUSTOMER SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBCustomerDAO::remove failed:" + removeQuery.lastError().text();
        return false;
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBCustomerDAO::remove dataset not found";
        return false;
    }

    return true;
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

