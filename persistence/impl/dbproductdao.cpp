#include "dbproductdao.h"

DBProductDAO::DBProductDAO(QSqlDatabase database, Validator<Product::Ptr>::Ptr validator)
 : m_database(database),
   m_validator(validator)
{

}

Product::Ptr DBProductDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBProductDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM PRODUCT WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving product failed" + query.lastError().text();
        throw new PersistenceException("retrieving product failed" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no product with id'" + QString::number(id) + "' found";
        throw new PersistenceException("no product with id'" + QString::number(id) + "' found");
    }

    return parseProduct(query.record());
}

QList<Product::Ptr> DBProductDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBProductDAO::getAll";

    QList<Product::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM PRODUCT WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving product failed" + query.lastError().text();
        throw new PersistenceException("retrieving product failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseProduct(query.record()));
    }

    return items;
}

void DBProductDAO::create(Product::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBProductDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO PRODUCT VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, 0);");

    insertQuery.addBindValue(item->name());
    insertQuery.addBindValue(item->manufactor());
    insertQuery.addBindValue(item->costPerUnit());
    insertQuery.addBindValue(item->pricePerUnit());
    insertQuery.addBindValue(item->type());
    insertQuery.addBindValue(item->unit());
    insertQuery.addBindValue(item->articleNumber());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBProductDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBProductDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());
}

void DBProductDAO::update(Product::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBProductDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE PRODUCT SET "
                        "NAME = ?, "
                        "MANUFACTOR = ?, "
                        "COST = ?, "
                        "PRICE = ?, "
                        "TYPE = ?, "
                        "UNIT = ?, "
                        "NR = ? "
                        "WHERE ID = ?;");

    updateQuery.addBindValue(item->name());
    updateQuery.addBindValue(item->manufactor());
    updateQuery.addBindValue(item->costPerUnit());
    updateQuery.addBindValue(item->pricePerUnit());
    updateQuery.addBindValue(item->type());
    updateQuery.addBindValue(item->unit());
    updateQuery.addBindValue(item->articleNumber());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBProductDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBProductDAO::update failed: " + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBProductDAO::update failed: dataset not found";
        throw new PersistenceException("DBProductDAO::update failed: dataset not found");
    }
}

void DBProductDAO::remove(Product::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBProductDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE PRODUCT SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBProductDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBProductDAO::remove failed: dataset not found");
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBProductDAO::remove failed: dataset not found";
        throw new PersistenceException("DBProductDAO::remove failed: dataset not found");
    }
}

Product::Ptr DBProductDAO::parseProduct(QSqlRecord record)
{
    Product::Ptr product = std::make_shared<Product>();

    product->setId(record.value("ID").toInt());
    product->setName(record.value("NAME").toString());
    product->setManufactor(record.value("MANUFACTOR").toString());
    product->setCostPerUnit(record.value("COST").toDouble());
    product->setPricePerUnit(record.value("PRICE").toDouble());
    product->setType(record.value("TYPE").toString());
    product->setUnit(record.value("UNIT").toString());
    product->setArticleNumber(record.value("NR").toString());

    return product;
}
