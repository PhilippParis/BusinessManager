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
        return nullptr;
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no product with id'" + QString::number(id) + "' found";
        return nullptr;
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
        return items;
    }

    while(query.next()) {
        items.append(parseProduct(query.record()));
    }

    return items;
}

bool DBProductDAO::create(Product::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBProductDAO::create with param " + item->toString();

    if (!m_validator->validateForCreate(item)) {
        return false;
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO PRODUCT VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, 0);");

    insertQuery.addBindValue(item->name());
    insertQuery.addBindValue(item->desc());
    insertQuery.addBindValue(item->costPerUnit());
    insertQuery.addBindValue(item->pricePerUnit());
    insertQuery.addBindValue(item->type());
    insertQuery.addBindValue(item->unit());
    insertQuery.addBindValue(item->stock());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBProductDAO::create failed: " + insertQuery.lastError().text();
        return false;
    }

    item->setId(insertQuery.lastInsertId().toInt());
    return true;
}

bool DBProductDAO::update(Product::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBProductDAO::update with param " + item->toString();

    if (!m_validator->validateForUpdate(item)) {
        return false;
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE PRODUCT SET "
                        "NAME = ?, "
                        "DESC = ?, "
                        "COST = ?, "
                        "PRICE = ?, "
                        "TYPE = ?, "
                        "UNIT = ?, "
                        "STOCK = ? "
                        "WHERE ID = ?;");

    updateQuery.addBindValue(item->name());
    updateQuery.addBindValue(item->desc());
    updateQuery.addBindValue(item->costPerUnit());
    updateQuery.addBindValue(item->pricePerUnit());
    updateQuery.addBindValue(item->type());
    updateQuery.addBindValue(item->unit());
    updateQuery.addBindValue(item->stock());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBProductDAO::update failed:" + updateQuery.lastError().text();
        return false;
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBProductDAO::update failed: dataset not found";
        return false;
    }

    return true;
}

bool DBProductDAO::remove(Product::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBProductDAO::remove with param " + item->toString();

    if (!m_validator->validateIdentity(item)) {
        return false;
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE PRODUCT SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBProductDAO::remove failed:" + removeQuery.lastError().text();
        return false;
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBProductDAO::remove failed: dataset not found";
        return false;
    }

    return true;
}

Product::Ptr DBProductDAO::parseProduct(QSqlRecord record)
{
    Product::Ptr product = std::make_shared<Product>();

    product->setId(record.value("ID").toInt());
    product->setName(record.value("NAME").toString());
    product->setDesc(record.value("DESC").toString());
    product->setCostPerUnit(record.value("COST").toDouble());
    product->setPricePerUnit(record.value("PRICE").toDouble());
    product->setType(record.value("TYPE").toString());
    product->setUnit(record.value("UNIT").toString());
    product->setStock(record.value("STOCK").toInt());

    return product;
}
