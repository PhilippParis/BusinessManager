#include "customerdaotest.h"

void CustomerDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_customerDAO = std::make_shared<DBCustomerDAO>(testDB, std::make_shared<CustomerValidator>());
}

void CustomerDAOTest::insertTest_data()
{
    QTest::addColumn<QString>("title");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("surname");
    QTest::addColumn<QString>("org");
    QTest::addColumn<QString>("city");
    QTest::addColumn<QString>("street");
    QTest::addColumn<QString>("mail");
    QTest::addColumn<bool>("result");

    QTest::newRow("nameEmpty_shouldFail") << "title" << "" << "surname" << "org" << "city" << "street" << "mail" << false;
    QTest::newRow("surnameEmpty_shouldFail") << "title" << "name" << "" << "org" << "city" << "street" << "mail" << false;
    QTest::newRow("cityEmpty_shouldFail") << "title" << "name" << "surname" << "org" << "" << "street" << "mail" << false;
    QTest::newRow("streetEmpty_shouldFail") << "title" << "name" << "surname" << "org" << "city" << "" << "mail" << false;

    QTest::newRow("orgEmpty_shouldPass") << "title" << "name" << "surname" << "" << "city" << "street" << "mail" << true;
    QTest::newRow("titleEmpty_shouldPass") << "" << "name" << "surname" << "org" << "city" << "street" << "mail" << true;
    QTest::newRow("mailEmpty_shouldPass") << "title" << "name" << "surname" << "org" << "city" << "street" << "" << true;

    QTest::newRow("validData_shouldPass") << "title" << "name" << "surname" << "org" << "city" << "street" << "mail" << true;
}

void CustomerDAOTest::insertTest()
{
    QFETCH(QString, title);
    QFETCH(QString, name);
    QFETCH(QString, surname);
    QFETCH(QString, org);
    QFETCH(QString, city);
    QFETCH(QString, street);
    QFETCH(QString, mail);
    QFETCH(bool, result);

    // PREPARE
    Customer::Ptr customer = std::make_shared<Customer>();
    customer->setTitle(title);
    customer->setName(name);
    customer->setSurname(surname);
    customer->setOrganisation(org);
    customer->setCity(city);
    customer->setStreet(street);
    customer->setMail(mail);

    // WHEN / THEN
    try {
        m_customerDAO->create(customer);
        QVERIFY(customer->id() >= 0);

        Customer::Ptr customerFromData = m_customerDAO->get(customer->id());
        QVERIFY(customer->equals(customerFromData));

    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void CustomerDAOTest::updateTest_data()
{
    QTest::addColumn<QString>("newTitle");
    QTest::addColumn<QString>("newName");
    QTest::addColumn<QString>("newSurname");
    QTest::addColumn<QString>("newOrg");
    QTest::addColumn<QString>("newCity");
    QTest::addColumn<QString>("newStreet");
    QTest::addColumn<QString>("newMail");

    QTest::addColumn<bool>("result");

    QTest::newRow("nameEmpty_shouldFail") << "title" << "" << "surname" << "org" << "city" << "street" << "mail" << false;
    QTest::newRow("surnameEmpty_shouldFail") << "title" << "name" << "" << "org" << "city" << "street" << "mail" << false;
    QTest::newRow("cityEmpty_shouldFail") << "title" << "name" << "surname" << "org" << "" << "street" << "mail" << false;
    QTest::newRow("streetEmpty_shouldFail") << "title" << "name" << "surname" << "org" << "city" << "" << "mail" << false;

    QTest::newRow("orgEmpty_shouldPass") << "title" << "name" << "surname" << "" << "city" << "street" << "mail" << true;
    QTest::newRow("titleEmpty_shouldPass") << "" << "name" << "surname" << "org" << "city" << "street" << "mail" << true;
    QTest::newRow("mailEmpty_shouldPass") << "title" << "name" << "surname" << "org" << "city" << "street" << "" << true;

    QTest::newRow("validData_shouldPass") << "title" << "name" << "surname" << "org" << "city" << "street" << "mail" << true;
}

void CustomerDAOTest::updateTest()
{
    QFETCH(QString, newTitle);
    QFETCH(QString, newName);
    QFETCH(QString, newSurname);
    QFETCH(QString, newOrg);
    QFETCH(QString, newCity);
    QFETCH(QString, newStreet);
    QFETCH(QString, newMail);
    QFETCH(bool, result);

    // PREPARE
    Customer::Ptr customer = std::make_shared<Customer>();
    customer->setTitle("title");
    customer->setName("name");
    customer->setSurname("surname");
    customer->setOrganisation("org");
    customer->setCity("city");
    customer->setStreet("street");
    customer->setMail("mail");

    m_customerDAO->create(customer);

    QVERIFY(customer->id() >= 0);

    // WHEN / THEN
    customer->setTitle(newTitle);
    customer->setName(newName);
    customer->setSurname(newSurname);
    customer->setOrganisation(newOrg);
    customer->setCity(newCity);
    customer->setStreet(newStreet);
    customer->setMail(newMail);

    try {
        m_customerDAO->update(customer);
        Customer::Ptr customerFromData = m_customerDAO->get(customer->id());
        QVERIFY(customer->equals(customerFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void CustomerDAOTest::updateWithInvalidIDTest()
{
    // PREPARE
    Customer::Ptr customer = std::make_shared<Customer>();
    customer->setTitle("title");
    customer->setName("name");
    customer->setSurname("surname");
    customer->setOrganisation("org");
    customer->setCity("city");
    customer->setStreet("street");
    customer->setMail("mail");

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_customerDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    customer->setId(id);

    try {
        m_customerDAO->update(customer);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void CustomerDAOTest::removeTestWithValidIDShouldPass()
{
    // PREPARE
    Customer::Ptr customer = std::make_shared<Customer>();
    customer->setTitle("title");
    customer->setName("name");
    customer->setSurname("surname");
    customer->setOrganisation("org");
    customer->setCity("city");
    customer->setStreet("street");
    customer->setMail("mail");

    m_customerDAO->create(customer);
    QVERIFY(customer->id() >= 0);

    int prevDataSetCount = m_customerDAO->getAll().size();

    // WHEN / THEN
    m_customerDAO->remove(customer);
    QCOMPARE(m_customerDAO->getAll().size(), prevDataSetCount - 1);
}

void CustomerDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    Customer::Ptr customer = std::make_shared<Customer>();
    customer->setTitle("title");
    customer->setName("name");
    customer->setSurname("surname");
    customer->setOrganisation("org");
    customer->setCity("city");
    customer->setStreet("street");
    customer->setMail("mail");

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_customerDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    customer->setId(id);

    // WHEN / THEN
    try {
        m_customerDAO->remove(customer);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void CustomerDAOTest::getAllTest()
{
    int prevDataSetCount = m_customerDAO->getAll().size();

    // PREPARE
    Customer::Ptr customer = std::make_shared<Customer>();
    customer->setTitle("title");
    customer->setName("name");
    customer->setSurname("surname");
    customer->setOrganisation("org");
    customer->setCity("city");
    customer->setStreet("street");
    customer->setMail("mail");

    // WHEN / THEN
    m_customerDAO->create(customer);
    QVERIFY(customer->id() >= 0);

    QCOMPARE(m_customerDAO->getAll().size(), prevDataSetCount + 1);
}
