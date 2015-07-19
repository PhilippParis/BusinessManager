#ifndef BILLITEMDAOTEST_H
#define BILLITEMDAOTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "persistence/impl/dbbillitemdao.h"
#include "persistence/impl/dbbilldao.h"
#include "persistence/impl/dbcustomerdao.h"

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/billvalidator.h"
#include "persistence/validation/impl/customervalidator.h"

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
    BillItemDAO *m_billItemDAO;
    BillDAO *m_billDAO;
    CustomerDAO *m_customerDAO;
};

#endif // BILLITEMDAOTEST_H
