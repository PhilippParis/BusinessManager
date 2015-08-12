#ifndef LETTERDAOTEST_H
#define LETTERDAOTEST_H

#include <memory>
#include <QObject>
#include <QSqlDatabase>
#include <QTest>

#include "persistence/persistenceexception.h"
#include "persistence/databasesingleton.h"
#include "persistence/validation/impl/customervalidator.h"
#include "persistence/validation/impl/lettervalidator.h"
#include "persistence/impl/dbcustomerdao.h"
#include "persistence/impl/dbhtmlfileletterdao.h"

class LetterDAOTest : public QObject
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
    std::shared_ptr<LetterDAO> m_letterDAO;

    Customer::Ptr m_validCustomer;
};

#endif // LETTERDAOTEST_H
