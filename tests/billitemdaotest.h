#ifndef BILLITEMDAOTEST_H
#define BILLITEMDAOTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "persistence/impl/dbbillitemdao.h"
#include "persistence/impl/dbbilldao.h"
#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/billvalidator.h"

class BillItemDAOTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    void insertTest_data();
    void insertTest();
    void updateTest();
    void removeTest();
    void getTest();

private:
    bool compareWithDatabase(BillItem::Ptr item, int billID);
    void prepareTestData();

private:
    BillItemDAO *m_billItemDao;
    BillDAO *m_billDao;
    QSqlDatabase m_database;
};

#endif // BILLITEMDAOTEST_H
