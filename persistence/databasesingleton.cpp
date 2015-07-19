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
                    "DATE REAL NOT NULL, "
                    "PAYED INTEGER NOT NULL, "
                    "CUSTOMER INTEGER NOT NULL REFERENCES CUSTOMER(ID), "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS DISCOUNT ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "TEXT VARCHAR(200) NOT NULL, "
                    "VALUE REAL NOT NULL, "
                    "BILL_ID INTEGER NOT NULL REFERENCES BILL, "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS BILL_ITEM ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "DESC VARCHAR(200) NOT NULL, "
                    "WORK_HOURS REAL NOT NULL, "
                    "WAGE REAL NOT NULL, "
                    "COST REAL NOT NULL, "
                    "PRICE REAL NOT NULL, "
                    "UNIT VARCHAR(20) NOT NULL, "
                    "QUANTITY INTEGER NOT NULL, "
                    "BILL INTEGER NOT NULL REFERENCES BILL(ID), "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS PRODUCT ( "
                    "ID INTEGER PRIMARY KEY NOT NULL, "
                    "NAME VARCHAR(200) NOT NULL, "
                    "DESC VARCHAR(200) NOT NULL, "
                    "COST REAL NOT NULL, "
                    "PRICE REAL NOT NULL, "
                    "SIZE VARCHAR(20) NOT NULL, "
                    "UNIT VARCHAR(20) NOT NULL, "
                    "STOCK REAL NOT NULL, "
                    "DELETED INTEGER NOT NULL DEFAULT 0);");

   if(!res) {
       qDebug() << query.lastError();
   }

   res = query.exec("CREATE TABLE IF NOT EXISTS PRODUCT_ITEM_ASSOC ( "
                    "PRODUCT_ID INTEGER NOT NULL REFERENCES PRODUCT(ID), "
                    "ITEM_ID INTEGER NOT NULL REFERENCES BILL_ITEM(ID), "
                    "QUANTITY INTEGER NOT NULL, "
                    "PRIMARY KEY(PRODUCT_ID, ITEM_ID));");

   if(!res) {
       qDebug() << query.lastError();
   }

}

DatabaseSingleton::DatabaseSingleton()
{

}



