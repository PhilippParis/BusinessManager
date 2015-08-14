#include "dbmaterialdao.h"

DBMaterialDAO::DBMaterialDAO(QSqlDatabase database, Validator<Material::Ptr>::Ptr validator)
 : m_database(database),
   m_validator(validator)
{

}

Material::Ptr DBMaterialDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBMaterialDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM MATERIAL WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving material failed" + query.lastError().text();
        throw new PersistenceException("retrieving material failed" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no material with id'" + QString::number(id) + "' found";
        throw new PersistenceException("no material with id'" + QString::number(id) + "' found");
    }

    return parseMaterial(query.record());
}

QList<Material::Ptr> DBMaterialDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBMaterialDAO::getAll";

    QList<Material::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM MATERIAL WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving material failed" + query.lastError().text();
        throw new PersistenceException("retrieving material failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseMaterial(query.record()));
    }

    return items;
}

void DBMaterialDAO::create(Material::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBMaterialDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO MATERIAL VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, 0);");

    insertQuery.addBindValue(item->name());
    insertQuery.addBindValue(item->manufactor());
    insertQuery.addBindValue(item->costPerUnit().cents());
    insertQuery.addBindValue(item->type());
    insertQuery.addBindValue(item->unit());
    insertQuery.addBindValue(item->articleNumber());
    insertQuery.addBindValue(item->taxRate());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBMaterialDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBMaterialDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());
}

void DBMaterialDAO::update(Material::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBMaterialDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE MATERIAL SET "
                        "NAME = ?, "
                        "MANUFACTOR = ?, "
                        "COST = ?, "
                        "TYPE = ?, "
                        "UNIT = ?, "
                        "NR = ?, "
                        "TAXRATE = ? "
                        "WHERE ID = ?;");

    updateQuery.addBindValue(item->name());
    updateQuery.addBindValue(item->manufactor());
    updateQuery.addBindValue(item->costPerUnit().cents());
    updateQuery.addBindValue(item->type());
    updateQuery.addBindValue(item->unit());
    updateQuery.addBindValue(item->articleNumber());
    updateQuery.addBindValue(item->taxRate());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBMaterialDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBMaterialDAO::update failed: " + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBMaterialDAO::update failed: dataset not found";
        throw new PersistenceException("DBMaterialDAO::update failed: dataset not found");
    }
}

void DBMaterialDAO::remove(Material::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBMaterialDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE MATERIAL SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBMaterialDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBMaterialDAO::remove failed: dataset not found");
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBMaterialDAO::remove failed: dataset not found";
        throw new PersistenceException("DBMaterialDAO::remove failed: dataset not found");
    }
}

Material::Ptr DBMaterialDAO::parseMaterial(QSqlRecord record)
{
    Material::Ptr material = std::make_shared<Material>();

    material->setId(record.value("ID").toInt());
    material->setName(record.value("NAME").toString());
    material->setManufactor(record.value("MANUFACTOR").toString());
    material->setCostPerUnit(Decimal::fromCents(record.value("COST").toInt()));
    material->setType(record.value("TYPE").toString());
    material->setUnit(record.value("UNIT").toString());
    material->setArticleNumber(record.value("NR").toString());
    material->setTaxRate(record.value("TAXRATE").toDouble());

    return material;
}
