#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H

#include <QtSql>

class DatabaseSingleton
{
public:
    static DatabaseSingleton *get();
    QSqlDatabase getTestDatabase();
    QSqlDatabase getProductionDatabase();

private:
    DatabaseSingleton();
    void createTables(QSqlDatabase db);

private:
    QSqlDatabase m_productionDatabase;
    QSqlDatabase m_testDatabase;
    static DatabaseSingleton *m_instance;
};

#endif // DATABASESINGLETON_H
