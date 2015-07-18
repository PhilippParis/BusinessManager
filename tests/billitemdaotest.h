#ifndef BILLITEMDAOTEST_H
#define BILLITEMDAOTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "persistence/impl/dbbillitemdao.h"
#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/billitemvalidator.h"

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
    BillItemDAO *m_dao;
    QSqlDatabase m_database;
};

#endif // BILLITEMDAOTEST_H
