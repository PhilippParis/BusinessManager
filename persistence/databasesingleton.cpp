#include "databasesingleton.h"

DatabaseSingleton *DatabaseSingleton::m_instance;

DatabaseSingleton *DatabaseSingleton::get()
{
    if (m_instance == nullptr) {
        m_instance = new DatabaseSingleton();
    }

    return m_instance;
}

QSqlDatabase DatabaseSingleton::getTestDatabase()
{
    if (!m_testDatabase.isOpen()) {
        m_testDatabase = QSqlDatabase::addDatabase("QSQLITE", "test_database");
        m_testDatabase.setDatabaseName(":memory:");
        if(!m_testDatabase.open()) {
            qFatal("testing database connection failed");
        }

        createTables(m_testDatabase);
    }

    return m_testDatabase;
}

QSqlDatabase DatabaseSingleton::getProductionDatabase()
{
    if (!m_productionDatabase.isOpen()) {
        m_productionDatabase = QSqlDatabase::addDatabase("QSQLITE", "production_database");
        m_productionDatabase.setDatabaseName("database.db");
        if(!m_productionDatabase.open()) {
            qFatal("production database connection failed");
        }

        createTables(m_productionDatabase);
    }

    return m_productionDatabase;
}

void DatabaseSingleton::createTables(QSqlDatabase db)
{
    QSqlQuery query(db);
    bool res = false;

    res = query.exec("PRAGMA synchronous = OFF");
    if(!res) {
        qDebug() << query.lastError();
    }

    res = query.exec("CREATE TABLE IF NOT EXISTS CUSTOMER ( "
                     "ID INTEGER PRIMARY KEY NOT NULL, "
                     "TITLE VARCHAR(20), "
                     "NAME VARCHAR(30) NOT NULL, "
                     "SURNAME VARCHAR(30) NOT NULL, "
                     "ORG VARCHAR(100), "
                     "MAIL VARCHAR(100), "
                     "CITY VARCHAR(50) NOT NULL, "
                     "STREET VARCHAR(50) NOT NULL, "
                     "DELETED INTEGER NOT NULL DEFAULT 0);");
   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS BILL ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "NR INTEGER NOT NULL, "
                    "DATE VARCHAR(20) NOT NULL, "
                    "PAYED INTEGER NOT NULL, "
                    "CUSTOMER INTEGER NOT NULL REFERENCES CUSTOMER(ID), "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS DISCOUNT ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "TEXT VARCHAR(200) NOT NULL, "
                    "VALUE INTEGER NOT NULL, "
                    "BILL INTEGER REFERENCES BILL, "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS ITEM ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "DESC VARCHAR(200) NOT NULL, "
                    "WORK_HOURS REAL NOT NULL, "
                    "WAGE INTEGER NOT NULL, "
                    "MATERIAL_COST INTEGER NOT NULL, "
                    "MATERIAL_OVERHEAD REAL NOT NULL, "
                    "FACTORY_OVERHEAD REAL NOT NULL, "
                    "PROFIT REAL NOT NULL, "
                    "CASHBACK REAL NOT NULL, "
                    "TAX REAL NOT NULL, "
                    "PRICE INTEGER NOT NULL, "
                    "UNIT VARCHAR(20) NOT NULL, "
                    "QUANTITY INTEGER NOT NULL, "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS BILL_ITEM ( "
                    "ID INTEGER PRIMARY KEY REFERENCES ITEM(ID), "
                    "BILL INTEGER REFERENCES BILL(ID));");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS MATERIAL ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "NAME VARCHAR(200) NOT NULL, "
                    "MANUFACTOR VARCHAR(200) NOT NULL, "
                    "COST INTEGER NOT NULL, "
                    "TYPE VARCHAR(20) NOT NULL, "
                    "UNIT VARCHAR(20) NOT NULL, "
                    "NR VARCHAR(20) NOT NULL, "
                    "TAX INTEGER NOT NULL, "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS MATERIAL_ITEM_ASSOC ( "
                    "MATERIAL_ID INTEGER NOT NULL REFERENCES MATERIAL(ID), "
                    "ITEM_ID INTEGER NOT NULL REFERENCES BILL_ITEM(ID), "
                    "QUANTITY INTEGER NOT NULL, "
                    "PRIMARY KEY(MATERIAL_ID, ITEM_ID));");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS TEMPLATE ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "NAME VARCHAR(200) NOT NULL, "
                    "ORG VARCHAR(200), "
                    "TYPE VARCHAR(200), "
                    "DESC VARCHAR(200), "
                    "ITEM_DESC VARCHAR(200) NOT NULL,"
                    "UNIT VARCHAR(20) NOT NULL, "
                    "WORK_HOURS REAL NOT NULL, "
                    "PRICE INTEGER NOT NULL, "
                    "TAXRATE REAL NOT NULL, "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS MATERIAL_TEMPLATE_ASSOC ( "
                    "MATERIAL_ID INTEGER NOT NULL REFERENCES MATERIAL(ID), "
                    "TEMPLATE_ID INTEGER NOT NULL REFERENCES TEMPLATE(ID), "
                    "QUANTITY INTEGER NOT NULL, "
                    "PRIMARY KEY(MATERIAL_ID, TEMPLATE_ID));");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS OFFER_ITEM ( "
                    "ID INTEGER PRIMARY KEY REFERENCES ITEM(ID), "
                    "OFFER INTEGER REFERENCES OFFER(ID));");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS OFFER ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "DATE VARCHAR(20) NOT NULL, "
                    "CUSTOMER INTEGER NOT NULL REFERENCES CUSTOMER(ID), "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS LETTER ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "DATE VARCHAR(20) NOT NULL, "
                    "CUSTOMER INTEGER NOT NULL REFERENCES CUSTOMER(ID), "
                    "FILEPATH VARCHAR(200) NOT NULL);");

   if(!res) {
       qDebug() << query.lastError();
   }
}

DatabaseSingleton::DatabaseSingleton()
{

}



