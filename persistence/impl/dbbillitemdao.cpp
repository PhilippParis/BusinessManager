#include "dbbillitemdao.h"

DBBillItemDAO::DBBillItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator, BillDAO::Ptr billDAO, ProductDAO::Ptr productDAO)
 : m_database(db),
   m_validator(validator),
   m_billDAO(billDAO),
   m_productDAO(productDAO)
{
}

void DBBillItemDAO::create(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO BILL_ITEM VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, ?, 0);");

    insertQuery.addBindValue(item->description());
    insertQuery.addBindValue(item->workingHours());
    insertQuery.addBindValue(item->wagePerHour());
    insertQuery.addBindValue(item->materialCost());
    insertQuery.addBindValue(item->price());
    insertQuery.addBindValue(item->unit());
    insertQuery.addBindValue(item->quantity());
    insertQuery.addBindValue(item->bill()->id());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillItemDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBBillItemDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());

    updateAssocTable(item);
}

void DBBillItemDAO::update(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE BILL_ITEM SET DESC = ?, "
                           "UNIT = ?, QUANTITY = ?, "
                           "PRICE = ?,  COST = ?, "
                           "WORK_HOURS = ?, WAGE = ?, "
                           "BILL = ? "
                           "WHERE ID = ?;");

    updateQuery.addBindValue(item->description());
    updateQuery.addBindValue(item->unit());
    updateQuery.addBindValue(item->quantity());
    updateQuery.addBindValue(item->price());
    updateQuery.addBindValue(item->materialCost());
    updateQuery.addBindValue(item->workingHours());
    updateQuery.addBindValue(item->wagePerHour());
    updateQuery.addBindValue(item->bill()->id());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillItemDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBBillItemDAO::update failed:" + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBBillItemDAO::update failed: dataset not found";
        throw new PersistenceException("DBBillItemDAO::update failed: dataset not found");
    }

    updateAssocTable(item);
}

void DBBillItemDAO::remove(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE BILL_ITEM SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillItemDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBBillItemDAO::remove failed:" + removeQuery.lastError().text());
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBBillItemDAO::remove failed: dataset not found";
        throw new PersistenceException("DBBillItemDAO::remove failed: dataset not found");
    }
}

BillItem::Ptr DBBillItemDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL_ITEM WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving billItem failed" + query.lastError().text();
        throw new PersistenceException("retrieving billItem failed" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no billItem with id'" + QString::number(id) + "' found";
        throw new PersistenceException("no billItem with id'" + QString::number(id) + "' found");
    }

    return parseBillItem(query.record());
}

QList<BillItem::Ptr> DBBillItemDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::getAll";

    QList<BillItem::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL_ITEM WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving billItems failed" + query.lastError().text();
        throw new PersistenceException("retrieving billItems failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseBillItem(query.record()));
    }

    return items;
}

QList<BillItem::Ptr> DBBillItemDAO::getItemsOfBill(int billID)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::getItemsOfBill";

    QList<BillItem::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL_ITEM WHERE DELETED = 0 AND BILL = ?");
    query.addBindValue(billID);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving billItems failed" + query.lastError().text();
        throw new PersistenceException("retrieving billItems failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseBillItem(query.record()));
    }

    return items;
}

BillItem::Ptr DBBillItemDAO::parseBillItem(QSqlRecord record)
{
    BillItem::Ptr item = std::make_shared<BillItem>();

    item->setId(record.value("ID").toInt());
    item->setDescription(record.value("DESC").toString());
    item->setMaterialCost(record.value("COST").toDouble());
    item->setPrice(record.value("PRICE").toDouble());
    item->setQuantity(record.value("QUANTITY").toDouble());
    item->setUnit(record.value("UNIT").toString());
    item->setWagePerHour(record.value("WAGE").toDouble());
    item->setWorkingHours(record.value("WORK_HOURS").toDouble());
    item->setBill(m_billDAO->get(record.value("BILL").toInt()));

    // get materials
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM PRODUCT_ITEM_ASSOC WHERE ITEM_ID = ?");
    query.addBindValue(item->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving product-item assocs failed" + query.lastError().text();
        throw new PersistenceException("retrieving product-item assocs failed" + query.lastError().text());
    }

    while(query.next()) {
        item->addMaterial(m_productDAO->get(query.value("PRODUCT_ID").toInt()),
                          query.value("QUANTITY").toDouble());
    }

    return item;
}

void DBBillItemDAO::updateAssocTable(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::updateAssocTable with param " + item->toString();

    QSqlQuery query(m_database);
    // remove all old entries
    query.prepare("DELETE FROM PRODUCT_ITEM_ASSOC WHERE ITEM_ID = ?");
    query.addBindValue(item->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "removing old product-item assocs failed" + query.lastError().text();
        throw new PersistenceException("removing old product-item assocs failed" + query.lastError().text());
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO PRODUCT_ITEM_ASSOC VALUES (?,?,?);");

    QMap<Product::Ptr, double> material = item->material();

    QMap<Product::Ptr, double>::iterator it;
    for (it = material.begin(); it != material.end(); ++it) {
        insertQuery.addBindValue(it.key()->id());
        insertQuery.addBindValue(item->id());
        insertQuery.addBindValue(it.value());

        if (!insertQuery.exec()) {
            qCCritical(lcPersistence) << "adding product-item assoc failed" + insertQuery.lastError().text();
            throw new PersistenceException("adding product-item assocs failed" + insertQuery.lastError().text());
        }
    }
}

