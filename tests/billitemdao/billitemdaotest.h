#ifndef BILLITEMDAOTEST_H
#define BILLITEMDAOTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "persistence/impl/dbbillitemdao.h"

class BillItemDAOTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void insertTest();
    void updateTest();
    void removeTest();
    void getTest();

private:
    BillItemDAO *m_dao;
};

#endif // BILLITEMDAOTEST_H
