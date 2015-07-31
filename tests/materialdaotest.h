#ifndef MATERIALDAOTEST_H
#define MATERIALDAOTEST_H

#include <QObject>
#include <QString>
#include <QtTest/QtTest>

#include "persistence/impl/dbmaterialdao.h"
#include "persistence/databasesingleton.h"
#include "persistence/validation/impl/materialvalidator.h"

class MaterialDAOTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    void insertTest_data();
    void insertTest();

    void updateTest_data();
    void updateTest();
    void updateWithInvalidIDTest();

    void removeTestWithValidIDShouldPass();
    void removeTestWithInValidIDShouldFail();

    void getAllTest();

private:
    MaterialDAO::Ptr m_materialDAO;
};

#endif // MATERIALDAOTEST_H
