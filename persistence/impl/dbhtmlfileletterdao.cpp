#include "dbhtmlfileletterdao.h"

DBHTMLFileLetterDAO::DBHTMLFileLetterDAO(QSqlDatabase database, Validator<Letter::Ptr>::Ptr validator, CustomerDAO::Ptr customerDAO)
 : m_database(database),
   m_validator(validator),
   m_customerDAO(customerDAO)
{

}

void DBHTMLFileLetterDAO::create(Letter::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBHTMLFileLetterDAO::create with param " + item->toString();

    try {
        m_validator->validateForCreate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    QString filePath = createHtmlFile(item);

    QSqlQuery insertQuery(m_database);
    insertQuery.prepare("INSERT INTO LETTER VALUES(NULL, ?, ?, ?);");

    insertQuery.addBindValue(item->date());
    insertQuery.addBindValue(item->customer()->id());
    insertQuery.addBindValue(filePath);

    if (!insertQuery.exec()) {
        QFile::remove(filePath);
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::create failed: " + insertQuery.lastError().text();
        throw new PersistenceException("DBHTMLFileLetterDAO::create failed: " + insertQuery.lastError().text());
    }

    item->setId(insertQuery.lastInsertId().toInt());
}

void DBHTMLFileLetterDAO::update(Letter::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBHTMLFileLetterDAO::update with param " + item->toString();

    try {
        m_validator->validateForUpdate(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    updateHtmlFile(item);

    QSqlQuery updateQuery(m_database);
    updateQuery.prepare("UPDATE LETTER SET DATE = ?, CUSTOMER = ? WHERE ID = ?;");
    updateQuery.addBindValue(item->date());
    updateQuery.addBindValue(item->customer()->id());
    updateQuery.addBindValue(item->id());

    if (!updateQuery.exec()) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::update failed:" + updateQuery.lastError().text();
        throw new PersistenceException("DBHTMLFileLetterDAO::update failed:" + updateQuery.lastError().text());
    }

    if (updateQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBHTMLFileLetterDAO::update dataset not found";
        throw new PersistenceException("DBHTMLFileLetterDAO::update dataset not found");
    }
}

void DBHTMLFileLetterDAO::remove(Letter::Ptr item)
{
    qCDebug(lcPersistence) << "Entering DBHTMLFileLetterDAO::remove with param " + item->toString();

    try {
        m_validator->validateIdentity(item);
    } catch (ValidationException *e) {
        throw new PersistenceException(e);
    }

    removeHtmlFile(item);

    QSqlQuery removeQuery(m_database);
    removeQuery.prepare("DELETE FROM LETTER WHERE ID = ?;");
    removeQuery.addBindValue(item->id());

    if (!removeQuery.exec()) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::remove failed:" + removeQuery.lastError().text();
        throw new PersistenceException("DBHTMLFileLetterDAO::remove failed:" + removeQuery.lastError().text());
    }

    if (removeQuery.numRowsAffected() == 0) {
        qCDebug(lcPersistence) << "DBHTMLFileLetterDAO::remove dataset not found";
        throw new PersistenceException("DBHTMLFileLetterDAO::remove dataset not found");
    }
}

Letter::Ptr DBHTMLFileLetterDAO::get(int id)
{
    qCDebug(lcPersistence) << "Entering DBHTMLFileLetterDAO::get with id " + QString::number(id);

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM LETTER WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::get failed:" + query.lastError().text();
        throw new PersistenceException("DBHTMLFileLetterDAO::get failed:" + query.lastError().text());
    }

    if (!query.next()) {
        qCDebug(lcPersistence) << "DBHTMLFileLetterDAO::get dataset not found";
        throw new PersistenceException("DBHTMLFileLetterDAO::get dataset not found");
    }

    return parseLetter(query.record());
}

QList<Letter::Ptr> DBHTMLFileLetterDAO::getAll()
{
    qCDebug(lcPersistence) << "Entering DBHTMLFileLetterDAO::getAll";

    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM LETTER");

    if (!query.exec()) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::getAll failed:" + query.lastError().text();
        throw new PersistenceException("DBHTMLFileLetterDAO::getAll failed:" + query.lastError().text());
    }

    QList<Letter::Ptr> items;
    while (query.next()) {
        items.append(parseLetter(query.record()));
    }

    return items;
}

Letter::Ptr DBHTMLFileLetterDAO::parseLetter(QSqlRecord record)
{
    Letter::Ptr letter = std::make_shared<Letter>();

    letter->setId(record.value("ID").toInt());
    letter->setDate(record.value("DATE").toDate());
    letter->setCustomer(m_customerDAO->get(record.value("CUSTOMER").toInt()));

    QTextDocument *doc = new QTextDocument();

    QFile file(record.value("FILEPATH").toString());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        doc->setHtml(QString::fromStdString(file.readAll().toStdString()));
        file.close();
    } else {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::parseLetter: html file not found";
    }

    letter->setTextDoc(doc);
    return letter;
}

QString DBHTMLFileLetterDAO::createHtmlFile(Letter::Ptr letter)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT COALESCE (MAX(ID) + 1, 0) AS NR FROM LETTER;");

    if (!query.exec() || !query.next()) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::createHtmlFile failed:" + query.lastError().text();
        throw new PersistenceException("DBHTMLFileLetterDAO::createHtmlFile failed:" + query.lastError().text());
    }

    QDir dir = QDir::current();
    if (!dir.exists("letters")) {
        dir.mkdir("letters");
    }

    int id = query.value("NR").toInt();
    QString filePath = QString("letters/letter_%1.html").arg(id);

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::creating file failed:";
        throw new PersistenceException("DBHTMLFileLetterDAO::creating file  failed:");
    }

    QTextStream out(&file);
    out << letter->textDoc()->toHtml();
    file.close();

    return filePath;
}

void DBHTMLFileLetterDAO::updateHtmlFile(Letter::Ptr letter)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT FILEPATH FROM LETTER WHERE ID = ?;");
    query.addBindValue(letter->id());

    if (!query.exec() || !query.next()) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::updateHtmlFile failed:" + query.lastError().text();
        throw new PersistenceException("DBHTMLFileLetterDAO::updateHtmlFile failed:" + query.lastError().text());
    }

    QString filePath = query.value("FILEPATH").toString();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::updateHtmlFile failed";
        throw new PersistenceException("DBHTMLFileLetterDAO::updateHtmlFile failed");
    }

    QTextStream out(&file);
    out << letter->textDoc()->toHtml();
    file.close();
}

void DBHTMLFileLetterDAO::removeHtmlFile(Letter::Ptr letter)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT FILEPATH FROM LETTER WHERE ID = ?;");
    query.addBindValue(letter->id());

    if (!query.exec() || !query.next()) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO::removeHtmlFile failed:" + query.lastError().text();
        throw new PersistenceException("DBHTMLFileLetterDAO::removeHtmlFile failed:" + query.lastError().text());
    }
    QString filePath = query.value("FILEPATH").toString();

    if (!QFile::exists(filePath)) {
        return;
    }

    if (!QFile::remove(filePath)) {
        qCCritical(lcPersistence) << "DBHTMLFileLetterDAO:: removing html file failed";
        throw new PersistenceException("DBHTMLFileLetterDAO:: removing html file failed");
    }
}

