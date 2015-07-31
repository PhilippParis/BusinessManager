#ifndef BILLITEMDAOTEST_H
#define BILLITEMDAOTEST_H

#include <QObject>
#include <QTest>

#include "persistence/impl/dbbillitemdao.h"
#include "persistence/impl/dbmaterialdao.h"

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/materialvalidator.h"

class BillItemDAOTest : public QObject
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
    BillItemDAO::Ptr m_billItemDAO;
    MaterialDAO::Ptr m_materialDAO;

    Material::Ptr m_validMaterial;
    Material::Ptr m_invalidMaterial;
    Material::Ptr m_nullMaterial;

};

#endif // BILLITEMDAOTEST_H
