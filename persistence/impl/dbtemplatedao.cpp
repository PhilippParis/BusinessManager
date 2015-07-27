#include "dbtemplatedao.h"

DBTemplateDAO::DBTemplateDAO(QSqlDatabase database, Validator<Template::Ptr>::Ptr validator, ProductDAO::Ptr productDAO)
 : m_database(database),
   m_validator(validator),
   m_productDAO(productDAO)
{

}

void DBTemplateDAO::create(Template::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBTemplateDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO TEMPLATE VALUES(NULL, ?, ?, ?, ?, ?, ?, ?, ?, 0);");

    insertQuery.addBindValue(item->name());
    insertQuery.addBindValue(item->organisation());
    insertQuery.addBindValue(item->type());
    insertQuery.addBindValue(item->desc());
    insertQuery.addBindValue(item->itemDesc());
    insertQuery.addBindValue(item->unit());
    insertQuery.addBindValue(item->workingHours());
    insertQuery.addBindValue(item->price());

    if (!insertQuery.exec()) {
        qCCritical(lcPersistence) << "DBTemplateDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBTemplateDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());
    updateAssocTable(item);
}

void DBTemplateDAO::update(Template::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBTemplateDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE TEMPLATE SET "
                        "NAME = ?, "
                        "ORG = ?, "
                        "TYPE = ?, "
                        "DESC = ?, "
                        "ITEM_DESC = ?, "
                        "UNIT = ?, "
                        "WORK_HOURS = ?, "
                        "PRICE = ? "
                        "WHERE ID = ?;");


    updateQuery.addBindValue(item->name());
    updateQuery.addBindValue(item->organisation());
    updateQuery.addBindValue(item->type());
    updateQuery.addBindValue(item->desc());
    updateQuery.addBindValue(item->itemDesc());
    updateQuery.addBindValue(item->unit());
    updateQuery.addBindValue(item->workingHours());
    updateQuery.addBindValue(item->price());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBTemplateDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBTemplateDAO::update failed:" + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBTemplateDAO::update dataset not found";
        throw new PersistenceException("DBTemplateDAO::update dataset not found");
    }

    updateAssocTable(item);
}

void DBTemplateDAO::remove(Template::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBTemplateDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("UPDATE TEMPLATE SET DELETED = 1 WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBTemplateDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBTemplateDAO::remove failed:" + removeQuery.lastError().text());
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBTemplateDAO::remove dataset not found";
        throw new PersistenceException("DBTemplateDAO::remove dataset not found");
    }
}

Template::Ptr DBTemplateDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBTemplateDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM TEMPLATE WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBTemplateDAO::get failed:" + query.lastError().text();
        throw new PersistenceException("DBTemplateDAO::get failed:" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "DBTemplateDAO::get dataset not found";
        throw new PersistenceException("DBTemplateDAO::get dataset not found");
    }

    return parseTemplate(query.record());
}

QList<Template::Ptr> DBTemplateDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBTemplateDAO::getAll";

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM TEMPLATE WHERE DELETED = 0");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBTemplateDAO::getAll failed:" + query.lastError().text();
        throw new PersistenceException("DBTemplateDAO::getAll failed:" + query.lastError().text());
    }

    QList<Template::Ptr> items;
    while (query.next()) {
        items.append(parseTemplate(query.record()));
    }

    return items;
}

Template::Ptr DBTemplateDAO::parseTemplate(QSqlRecord record)
{
    Template::Ptr templ = std::make_shared<Template>();

    templ->setId(record.value("ID").toInt());
    templ->setName(record.value("NAME").toString());
    templ->setOrganisation(record.value("ORG").toString());
    templ->setType(record.value("TYPE").toString());
    templ->setDesc(record.value("DESC").toString());
    templ->setItemDesc(record.value("ITEM_DESC").toString());
    templ->setUnit(record.value("UNIT").toString());
    templ->setWorkingHours(record.value("WORK_HOURS").toDouble());
    templ->setPrice(record.value("PRICE").toDouble());

    // get materials
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM PRODUCT_TEMPLATE_ASSOC WHERE TEMPLATE_ID = ?");
    query.addBindValue(templ->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "retrieving product-template assocs failed" + query.lastError().text();
        throw new PersistenceException("retrieving product-template assocs failed" + query.lastError().text());
    }

    QMap<Product::Ptr, double> material;
    while(query.next()) {
        material.insert(m_productDAO->get(query.value("PRODUCT_ID").toInt()),
                        query.value("QUANTITY").toDouble());
    }

    templ->setMaterial(material);

    return templ;
}

void DBTemplateDAO::updateAssocTable(Template::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBTemplateDAO::updateAssocTable with param " + item->toString();

    QSqlQuery query(m_database);
    // remove all old entries
    query.prepare("DELETE FROM PRODUCT_TEMPLATE_ASSOC WHERE TEMPLATE_ID = ?");
    query.addBindValue(item->id());

    if (!query.exec()) {
        qCCritical(lcPersistence) << "removing old product-template assocs failed" + query.lastError().text();
        throw new PersistenceException("removing old product-template assocs failed" + query.lastError().text());
    }

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO PRODUCT_TEMPLATE_ASSOC VALUES (?,?,?);");

    QMap<Product::Ptr, double> material = item->material();

    QMap<Product::Ptr, double>::iterator it;
    for (it = material.begin(); it != material.end(); ++it) {
        insertQuery.addBindValue(it.key()->id());
        insertQuery.addBindValue(item->id());
        insertQuery.addBindValue(it.value());

        if (!insertQuery.exec()) {
            qCCritical(lcPersistence) << "adding product-template assoc failed" + insertQuery.lastError().text();
            throw new PersistenceException("adding product-template assocs failed" + insertQuery.lastError().text());
        }
    }
}
