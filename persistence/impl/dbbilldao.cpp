#include "dbbilldao.h"

DBBillDAO::DBBillDAO(QSqlDatabase database, Validator<Bill::Ptr>::Ptr validator, CustomerDAO::Ptr customerDAO,
                     BillItemDAO::Ptr billItemDAO, DiscountDAO::Ptr discountDAO)
 : m_database(database),
   m_validator(validator),
   m_customerDAO(customerDAO),
   m_billItemDAO(billItemDAO),
   m_discountDAO(discountDAO)
{
}

Bill::Ptr DBBillDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving bill failed" + query.lastError().text();
        throw new PersistenceException("retrieving bill failed" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "no bill with id'" + QString::number(id) + "' found";
        throw new PersistenceException("no bill with id'" + QString::number(id) + "' found");
    }

    return parseBill(query.record());
}

QList<Bill::Ptr> DBBillDAO::get(QDate from, QDate to)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::get between: " << from.toString() << " - " << to.toString();

    QList<Bill::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL WHERE JULIANDAY(DATE) >= JULIANDAY(?) AND JULIANDAY(DATE) <= JULIANDAY(?) AND DELETED = 0");
    query.addBindValue(from);
    query.addBindValue(to);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving bills failed" + query.lastError().text();
        throw new PersistenceException("retrieving bill failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseBill(query.record()));
    }

    return items;
}

QList<Bill::Ptr> DBBillDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::getAll";

    QList<Bill::Ptr> items;
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM BILL WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving bills failed" + query.lastError().text();
        throw new PersistenceException("retrieving bill failed" + query.lastError().text());
    }

    while(query.next()) {
        items.append(parseBill(query.record()));
    }

    return items;
}

void DBBillDAO::create(Bill::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO BILL VALUES(NULL, ?, ?, ?, ?, 0);");

    insertQuery.addBindValue(item->billNumber());
    insertQuery.addBindValue(item->date().toString("yyyy-MM-dd"));
    insertQuery.addBindValue(item->payed());
    insertQuery.addBindValue(item->customer()->id());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBBillDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());
    updateBillItems(item);
    updateDiscounts(item);
}

void DBBillDAO::update(Bill::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE BILL SET "
                        "NR = ?, "
                        "DATE = ?, "
                        "PAYED = ?, "
                        "CUSTOMER = ? "
                        "WHERE ID = ?;");

    updateQuery.addBindValue(item->billNumber());
    updateQuery.addBindValue(item->date().toString("yyyy-MM-dd"));
    updateQuery.addBindValue(item->payed());
    updateQuery.addBindValue(item->customer()->id());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBBillDAO::update failed: " + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBBillDAO::update failed: dataset not found";
        throw new PersistenceException("DBBillDAO::update failed: dataset not found");
    }

    updateBillItems(item);
    updateDiscounts(item);
}

void DBBillDAO::remove(Bill::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE BILL SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBBillDAO::remove failed:" + removeQuery.lastError().text());
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBBillDAO::remove failed: dataset not found";
        throw new PersistenceException("DBBillDAO::remove failed: dataset not found");
    }
}

int DBBillDAO::nextBillNumber(QDate date)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::nextBillNumber with param QDate: " + date.toString("yyyy-MM-dd");

    QSqlQuery query(m_database);
    query.prepare("SELECT COALESCE (MAX(NR) + 1, 1) AS NEXT FROM BILL WHERE STRFTIME('%Y', DATE) = ? AND DELETED = 0;");
    query.addBindValue(QString::number(date.year()));

    if (!query.exec() || !query.next()) {
        qCCritical(lcPersistence) << "DBBillDAO::nextBillNumber failed:" + query.lastError().text();
        throw new PersistenceException("DBBillDAO::nextBillNumber failed:" + query.lastError().text());
    }

    return query.value("NEXT").toInt();
}

QPair<QDate, QDate> DBBillDAO::billDateRange()
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::billDateRange ";

    QSqlQuery query(m_database);
    query.prepare("SELECT MIN(JULIANDAY(DATE)) AS MINT, MAX(JULIANDAY(DATE)) AS MAXT FROM BILL WHERE DELETED = 0;");

    if (!query.exec() || !query.next()) {
        qCCritical(lcPersistence) << "DBBillDAO::billDateRange failed:" + query.lastError().text();
        throw new PersistenceException("DBBillDAO::billDateRange failed:" + query.lastError().text());
    }

    return QPair<QDate,QDate>(QDate::fromJulianDay(query.value("MINT").toInt()),
                              QDate::fromJulianDay(query.value("MAXT").toInt()));
}

Bill::Ptr DBBillDAO::parseBill(QSqlRecord record)
{
    Bill::Ptr bill = std::make_shared<Bill>();

    bill->setId(record.value("ID").toInt());
    bill->setBillNumber(record.value("NR").toInt());
    bill->setPayed(record.value("PAYED").toBool());
    bill->setDate(QDate::fromString(record.value("DATE").toString(), "yyyy-MM-dd"));
    bill->setCustomer(m_customerDAO->get(record.value("CUSTOMER").toInt()));

    // get items
    QSqlQuery query(m_database);
    query.prepare("SELECT ID FROM BILL_ITEM WHERE BILL = ?;");
    query.addBindValue(bill->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::parseBill failed:" + query.lastError().text();
        throw new PersistenceException("DBBillDAO::parseBill failed:" + query.lastError().text());
    }

    QList<BillItem::Ptr> items;
    while(query.next()) {
        items.append(m_billItemDAO->get(query.value("ID").toInt()));
    }
    bill->setItems(items);

    // get discounts
    query.prepare("SELECT ID FROM DISCOUNT WHERE BILL = ?;");
    query.addBindValue(bill->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::parseBill failed:" + query.lastError().text();
        throw new PersistenceException("DBBillDAO::parseBill failed:" + query.lastError().text());
    }

    QList<Discount::Ptr> discounts;
    while(query.next()) {
        discounts.append(m_discountDAO->get(query.value("ID").toInt()));
    }
    bill->setDiscounts(discounts);

    return bill;
}

void DBBillDAO::updateBillItems(Bill::Ptr bill)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::updateBillItems with param " + bill->toString();
    QList<BillItem::Ptr> items = bill->items();

    // set all already stored items as deleted
    QSqlQuery query(m_database);
    query.prepare("UPDATE BILL_ITEM SET DELETED = 1 WHERE BILL = ?;");
    query.addBindValue(bill->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::updateBillItems failed:" + query.lastError().text();
        throw new PersistenceException("DBBillDAO::updateBillItems failed:" + query.lastError().text());
    }

    QStringList placeholders;
    for (int i = 0; i < items.size(); ++i) {
         placeholders << "?";
    }

    // enable items and set bill id
    query.prepare("UPDATE BILL_ITEM SET BILL = ?, DELETED = 0 WHERE ID IN (" + placeholders.join(", ") + ")");
    query.addBindValue(bill->id());
    for (int i = 0; i < items.size(); ++i) {
         query.addBindValue(items.at(i)->id());
    }

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::updateBillItems failed:" + query.lastError().text();
        throw new PersistenceException("DBBillDAO::updateBillItems failed:" + query.lastError().text());
    }
}

void DBBillDAO::updateDiscounts(Bill::Ptr bill)
{
    qCDebug(lcPersistence) << "Entering DBBillDAO::updateDiscounts with param " + bill->toString();
    QList<Discount::Ptr> discounts = bill->discounts();

    // set all already stored items as deleted
    QSqlQuery query(m_database);
    query.prepare("UPDATE DISCOUNT SET DELETED = 1 WHERE BILL = ?;");
    query.addBindValue(bill->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::updateDiscounts failed:" + query.lastError().text();
        throw new PersistenceException("DBBillDAO::updateDiscounts failed:" + query.lastError().text());
    }

    QStringList placeholders;
    for (int i = 0; i < discounts.size(); ++i) {
         placeholders << "?";
    }

    // enable items and set bill id
    query.prepare("UPDATE DISCOUNT SET BILL = ?, DELETED = 0 WHERE ID IN (" + placeholders.join(", ") + ")");
    query.addBindValue(bill->id());
    for (int i = 0; i < discounts.size(); ++i) {
         query.addBindValue(discounts.at(i)->id());
    }

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBBillDAO::updateDiscounts failed:" + query.lastError().text();
        throw new PersistenceException("DBBillDAO::updateDiscounts failed:" + query.lastError().text());
    }
}


