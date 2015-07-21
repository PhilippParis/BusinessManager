#ifndef CUSTOMERDAOTEST_H
#define CUSTOMERDAOTEST_H

#include <memory>
#include <QObject>
#include <QSqlDatabase>
#include <QTest>

#include "persistence/persistenceexception.h"
#include "persistence/databasesingleton.h"
#include "persistence/validation/impl/customervalidator.h"
#include "persistence/impl/dbcustomerdao.h"

class CustomerDAOTest : public QObject
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
    std::shared_ptr<CustomerDAO> m_customerDAO;
};

#endif // CUSTOMERDAOTEST_H
