#include "dbbillitemdao.h"

DBBillItemDAO::DBBillItemDAO(QSqlDatabase db)
 : m_database(db)
{
    m_insertQuery.prepare("INSERT INTO BILL_ITEM VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?);");

    m_updateQuery.prepare("UPDATE BILL_ITEM SET DESCRIPTION = ?,  \
                           UNIT = ?, QUANTITY = ?,  \
                           PRICE = ?,  COST = ?,  \
                           WORKING_HOURS = ?, WAGE = ? \
                           WHERE ID = ?;");

    m_removeQuery.prepare("REMOVE FROM BILL_ITEM WHERE ID = ?;");
}

DBBillItemDAO::~DBBillItemDAO()
{
    m_insertQuery.clear();
    m_updateQuery.clear();
    m_removeQuery.clear();
}

BillItem::Ptr DBBillItemDAO::getFromDataSource(int id)
{
    QSqlQuery query;
    query.exec("SELECT FROM BILL_ITEM WHERE ID = " + QString::number(id));

    if(!query.exec() || !query.next()) {
        // TODO Logging
        return nullptr;
    }

    return parseBillItem(query.record());
}

bool DBBillItemDAO::writeToDataSource(BillItem::Ptr item, int billID)
{
    m_insertQuery.addBindValue(item->description());
    m_insertQuery.addBindValue(item->unit());
    m_insertQuery.addBindValue(item->quantity());
    m_insertQuery.addBindValue(item->price());
    m_insertQuery.addBindValue(item->materialCost());
    m_insertQuery.addBindValue(billID);
    m_insertQuery.addBindValue(item->workingHours());
    m_insertQuery.addBindValue(item->wagePerHour());

    bool result = m_insertQuery.exec();
    // TODO: logging!
    return result;
}

bool DBBillItemDAO::updateInDataSource(BillItem::Ptr item)
{
    m_updateQuery.addBindValue(item->description());
    m_updateQuery.addBindValue(item->unit());
    m_updateQuery.addBindValue(item->quantity());
    m_updateQuery.addBindValue(item->price());
    m_updateQuery.addBindValue(item->materialCost());
    m_updateQuery.addBindValue(item->workingHours());
    m_updateQuery.addBindValue(item->wagePerHour());
    m_updateQuery.addBindValue(item->id());

    bool result = m_updateQuery.exec();
    // TODO Logging!
    return result;
}

bool DBBillItemDAO::removeFromDataSource(BillItem::Ptr item)
{
    m_removeQuery.addBindValue(item->id());
    bool result = m_removeQuery.exec();
    // TODO Logging!
    return result;
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

