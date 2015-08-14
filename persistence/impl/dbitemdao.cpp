#include "dbitemdao.h"

DBItemDAO::DBItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator, MaterialDAO::Ptr materialDAO)
 : m_database(db),
   m_validator(validator),
   m_materialDAO(materialDAO)
{
}

void DBItemDAO::create(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBItemDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO ITEM VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 0);");

    insertQuery.addBindValue(item->description());
    insertQuery.addBindValue(item->workingHours());
    insertQuery.addBindValue(item->wagePerHour().cents());
    insertQuery.addBindValue(item->materialNetCost().cents());
    insertQuery.addBindValue(item->materialCost().cents());
    insertQuery.addBindValue(item->materialOverhead());
    insertQuery.addBindValue(item->factoryOverhead());
    insertQuery.addBindValue(item->profit());
    insertQuery.addBindValue(item->cashback());
    insertQuery.addBindValue(item->taxRate());
    insertQuery.addBindValue(item->price().cents());
    insertQuery.addBindValue(item->unit());
    insertQuery.addBindValue(item->quantity());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBItemDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBItemDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());

    updateAssocTable(item);
}

void DBItemDAO::update(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBItemDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE ITEM SET DESC = ?, "
                           "WORK_HOURS = ?, WAGE = ?, "
                           "MATERIAL_NETCOST = ?, MATERIAL_COST = ?, MATERIAL_OVERHEAD = ?, "
                           "FACTORY_OVERHEAD = ?, PROFIT = ?, "
                           "CASHBACK = ?, TAX = ?, "
                           "PRICE = ?, UNIT = ?, "
                           "QUANTITY = ? WHERE ID = ?;"
                        );

    updateQuery.addBindValue(item->description());
    updateQuery.addBindValue(item->workingHours());
    updateQuery.addBindValue(item->wagePerHour().cents());
    updateQuery.addBindValue(item->materialNetCost().cents());
    updateQuery.addBindValue(item->materialCost().cents());
    updateQuery.addBindValue(item->materialOverhead());
    updateQuery.addBindValue(item->factoryOverhead());
    updateQuery.addBindValue(item->profit());
    updateQuery.addBindValue(item->cashback());
    updateQuery.addBindValue(item->taxRate());
    updateQuery.addBindValue(item->price().cents());
    updateQuery.addBindValue(item->unit());
    updateQuery.addBindValue(item->quantity());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBItemDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBItemDAO::update failed:" + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBItemDAO::update failed: dataset not found";
        throw new PersistenceException("DBItemDAO::update failed: dataset not found");
    }

    updateAssocTable(item);
}

void DBItemDAO::remove(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBItemDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE ITEM SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBItemDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBItemDAO::remove failed:" + removeQuery.lastError().text());
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBItemDAO::remove failed: dataset not found";
        throw new PersistenceException("DBItemDAO::remove failed: dataset not found");
    }
}

BillItem::Ptr DBItemDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBItemDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM ITEM WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving billItem failed" + query.lastError().text();
        throw new PersistenceException("retrieving billItem failed" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no billItem with id'" + QString::number(id) + "' found";
        throw new PersistenceException("no billItem with id'" + QString::number(id) + "' found");
    }

    return parseItem(query.record());
}

QList<BillItem::Ptr> DBItemDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBItemDAO::getAll";

    QList<BillItem::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM ITEM WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving billItems failed" + query.lastError().text();
        throw new PersistenceException("retrieving billItems failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseItem(query.record()));
    }

    return items;
}

BillItem::Ptr DBItemDAO::parseItem(QSqlRecord record)
{
    BillItem::Ptr item = std::make_shared<BillItem>();

    item->setId(record.value("ID").toInt());
    item->setDescription(record.value("DESC").toString());
    item->setMaterialNetCost(Decimal::fromCents(record.value("MATERIAL_NETCOST").toInt()));
    item->setMaterialCost(Decimal::fromCents(record.value("MATERIAL_COST").toInt()));
    item->setMaterialOverhead(record.value("MATERIAL_OVERHEAD").toDouble());
    item->setFactoryOverhead(record.value("FACTORY_OVERHEAD").toDouble());
    item->setProfit(record.value("PROFIT").toDouble());
    item->setCashback(record.value("CASHBACK").toDouble());
    item->setTaxRate(record.value("TAX").toDouble());
    item->setPrice(Decimal::fromCents(record.value("PRICE").toInt()));
    item->setQuantity(record.value("QUANTITY").toDouble());
    item->setUnit(record.value("UNIT").toString());
    item->setWagePerHour(Decimal::fromCents(record.value("WAGE").toInt()));
    item->setWorkingHours(record.value("WORK_HOURS").toDouble());

    // get materials
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM MATERIAL_ITEM_ASSOC WHERE ITEM_ID = ?");
    query.addBindValue(item->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving material-item assocs failed" + query.lastError().text();
        throw new PersistenceException("retrieving material-item assocs failed" + query.lastError().text());
    }

    QMap<Material::Ptr, double> material;
    while(query.next()) {
        material.insert(m_materialDAO->get(query.value("MATERIAL_ID").toInt()),
                        query.value("QUANTITY").toDouble());
    }

    item->setMaterial(material);
    return item;
}

void DBItemDAO::updateAssocTable(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBItemDAO::updateAssocTable with param " + item->toString();

    QSqlQuery query(m_database);
    // remove all old entries
    query.prepare("DELETE FROM MATERIAL_ITEM_ASSOC WHERE ITEM_ID = ?");
    query.addBindValue(item->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "removing old material-item assocs failed" + query.lastError().text();
        throw new PersistenceException("removing old material-item assocs failed" + query.lastError().text());
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO MATERIAL_ITEM_ASSOC VALUES (?,?,?);");

    QMap<Material::Ptr, double> material = item->material();

    QMap<Material::Ptr, double>::iterator it;
    for (it = material.begin(); it != material.end(); ++it) {
        insertQuery.addBindValue(it.key()->id());
        insertQuery.addBindValue(item->id());
        insertQuery.addBindValue(it.value());

        if (!insertQuery.exec()) {
            qCCritical(lcPersistence) << "adding material-item assoc failed" + insertQuery.lastError().text();
            throw new PersistenceException("adding material-item assocs failed" + insertQuery.lastError().text());
        }
    }
}


