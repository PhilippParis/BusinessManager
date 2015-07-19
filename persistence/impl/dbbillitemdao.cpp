#include "dbbillitemdao.h"

DBBillItemDAO::DBBillItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator)
 : m_database(db),
   m_validator(validator)
{
}

DBBillItemDAO::~DBBillItemDAO()
{
}

bool DBBillItemDAO::create(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::create with param " + item->toString();

    if (!m_validator->validateForCreate(item)) {
        return false;
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
        return false;
    }

    return true;
}

bool DBBillItemDAO::update(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::update with param " + item->toString();

    if (!m_validator->validateForUpdate(item)) {
        return false;
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE BILL_ITEM SET DESCRIPTION = ?,  \
                           UNIT = ?, QUANTITY = ?,  \
                           PRICE = ?,  COST = ?,  \
                           WORKING_HOURS = ?, WAGE = ? \
                           WHERE ID = ?;");

    updateQuery.addBindValue(item->description());
    updateQuery.addBindValue(item->unit());
    updateQuery.addBindValue(item->quantity());
    updateQuery.addBindValue(item->price());
    updateQuery.addBindValue(item->materialCost());
    updateQuery.addBindValue(item->workingHours());
    updateQuery.addBindValue(item->wagePerHour());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillItemDAO::update failed:" + updateQuery.lastError().text();
        return false;
    }

    return true;
}

bool DBBillItemDAO::remove(BillItem::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::remove with param " + item->toString();

    if (!m_validator->validateIdentity(item)) {
        return false;
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE BILL_ITEM SET DELETED = true WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillItemDAO::remove failed:" + removeQuery.lastError().text();
        return false;
    }

    return true;
}

BillItem::Ptr DBBillItemDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::get with id " + QString::number(id);

    QSqlQuery query;
    query.prepare("SELECT * FROM BILL_ITEM WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving billItem failed" + query.lastError().text();
        return nullptr;
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no billItem with id'" + QString::number(id) + "' found";
        return nullptr;
    }

    return parseBillItem(query.record());
}

QList<BillItem::Ptr> DBBillItemDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBBillItemDAO::getAll";

    QList<BillItem::Ptr> items;
    QSqlQuery query;
    query.prepare("SELECT * FROM BILL_ITEM WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving billItems failed" + query.lastError().text();
        return items;
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

    return item;
}

