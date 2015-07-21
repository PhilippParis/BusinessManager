#ifndef PRODUCTDAOTEST_H
#define PRODUCTDAOTEST_H

#include <QObject>
#include <QString>
#include <QtTest/QtTest>

#include "persistence/impl/dbproductdao.h"
#include "persistence/databasesingleton.h"
#include "persistence/validation/impl/productvalidator.h"


class ProductDAOTest : public QObject
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
    ProductDAO::Ptr m_productDAO;
};

#endif // PRODUCTDAOTEST_H
