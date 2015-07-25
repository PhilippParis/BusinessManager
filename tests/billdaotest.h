#ifndef BILLDAOTEST_H
#define BILLDAOTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "persistence/impl/dbbilldao.h"
#include "persistence/impl/dbcustomerdao.h"
#include "persistence/impl/dbbillitemdao.h"
#include "persistence/impl/dbproductdao.h"
#include "persistence/impl/dbdiscountdao.h"

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/billvalidator.h"
#include "persistence/validation/impl/customervalidator.h"
#include "persistence/validation/impl/discountvalidator.h"

class BillDAOTest : public QObject
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
    BillDAO::Ptr m_billDAO;
    BillItemDAO::Ptr m_billItemDAO;
    CustomerDAO::Ptr m_customerDAO;
    ProductDAO::Ptr m_productDAO;

    BillItem::Ptr m_validBillItem;
    Customer::Ptr m_validCustomer;
};

#endif // BILLDAOTEST_H
