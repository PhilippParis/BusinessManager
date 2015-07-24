#ifndef BILLITEMDAOTEST_H
#define BILLITEMDAOTEST_H

#include <QObject>
#include <QTest>

#include "persistence/impl/dbbillitemdao.h"
#include "persistence/impl/dbcustomerdao.h"
#include "persistence/impl/dbproductdao.h"

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/customervalidator.h"
#include "persistence/validation/impl/productvalidator.h"

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
    CustomerDAO::Ptr m_customerDAO;
    ProductDAO::Ptr m_productDAO;

    Product::Ptr m_validProduct;
    Product::Ptr m_invalidProduct;
    Product::Ptr m_nullProduct;

};

#endif // BILLITEMDAOTEST_H
