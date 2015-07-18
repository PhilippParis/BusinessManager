#include "dbbillitemdao.h"

DBBillItemDAO::DBBillItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator)
 : m_database(db),
   m_validator(validator)
{
}

DBBillItemDAO::~DBBillItemDAO()
{
}

bool DBBillItemDAO::write(BillItem::Ptr item, int billID)
{
    if(!m_validator->validateForCreate(item)) {
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
    insertQuery.addBindValue(billID);

    bool result = insertQuery.exec();
    if(!result) {
        qDebug() << insertQuery.lastError();
    }

    // TODO: logging!
    return result;
}

bool DBBillItemDAO::update(BillItem::Ptr item)
{
    if(!m_validator->validateForUpdate(item)) {
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

    bool result = updateQuery.exec();
    // TODO Logging!
    return result;
}

bool DBBillItemDAO::remove(BillItem::Ptr item)
{
    if(!m_validator->validateIdentity(item)) {
        return false;
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE BILL_ITEM SET DELETED = true WHERE ID = ?;");

    removeQuery.addBindValue(item->id());
    bool result = removeQuery.exec();
    // TODO Logging!
    return result;
}

BillItem::Ptr DBBillItemDAO::get(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM BILL_ITEM WHERE ID = ?");
    query.addBindValue(id);

    if(!query.exec() || !query.next()) {
        // TODO Logging
        return nullptr;
    }

    return parseBillItem(query.record());
}

BillItem::Ptr DBBillItemDAO::parseBillItem(QSqlRecord record)
{
    BillItem::Ptr item = std::make_shared<BillItem>();

    item->setId(record.value("ID").toInt());
    item->setDescription(record.value("DESCRIPTION").toString());
    item->setMaterialCost(record.value("COST").toDouble());
    item->setPrice(record.value("PRICE").toDouble());
    item->setQuantity(record.value("QUANTITY").toDouble());
    item->setUnit(record.value("UNIT").toString());
    item->setWagePerHour(record.value("WAGE").toDouble());
    item->setWorkingHours(record.value("WORKING_HOURS").toDouble());

    return item;
}

