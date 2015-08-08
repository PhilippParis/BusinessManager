#ifndef OFFERDAOTEST_H
#define OFFERDAOTEST_H


#include <QObject>
#include <QtTest/QtTest>

#include "persistence/impl/dbofferdao.h"
#include "persistence/impl/dbcustomerdao.h"
#include "persistence/impl/dbofferitemdao.h"
#include "persistence/impl/dbmaterialdao.h"

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/offervalidator.h"
#include "persistence/validation/impl/customervalidator.h"

class OfferDAOTest : public QObject
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
    OfferDAO::Ptr m_offerDAO;
    OfferItemDAO::Ptr m_offerItemDAO;
    CustomerDAO::Ptr m_customerDAO;
    MaterialDAO::Ptr m_materialDAO;

    BillItem::Ptr m_validOfferItem;
    Customer::Ptr m_validCustomer;
};

#endif // OFFERDAOTEST_H
