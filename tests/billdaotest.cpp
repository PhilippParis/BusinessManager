#include "billdaotest.h"

void BillDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_customerDAO = std::make_shared<DBCustomerDAO>(testDB, std::make_shared<CustomerValidator>());
    m_billDAO = std::make_shared<DBBillDAO>(testDB, std::make_shared<BillValidator>(), m_customerDAO);

    m_validCustomer = std::make_shared<Customer>();
    m_validCustomer->setTitle("title");
    m_validCustomer->setName("name");
    m_validCustomer->setSurname("surname");
    m_validCustomer->setOrganisation("org");
    m_validCustomer->setCity("city");
    m_validCustomer->setStreet("street");
    m_validCustomer->setMail("mail");

    QCOMPARE(m_customerDAO->create(m_validCustomer), true);
    QVERIFY(m_validCustomer->id() >= 0);
}

void BillDAOTest::insertTest_data()
{
    QTest::addColumn<Customer::Ptr>("customer");
    QTest::addColumn<int>("number");
    QTest::addColumn<QDate>("date");
    QTest::addColumn<bool>("payed");
    QTest::addColumn<bool>("result");

    Customer::Ptr invalidCustomer = std::make_shared<Customer>();
    Customer::Ptr noCustomer = nullptr;

    QTest::newRow("validData_shouldPass") << m_validCustomer << 1 << QDate::currentDate() << true << true;

    QTest::newRow("invalidCustomer_shouldFail") << invalidCustomer << 2 << QDate::currentDate() << true << false;
    QTest::newRow("noCustomer_shouldFail") << noCustomer << 3 << QDate::currentDate() << true << false;
    QTest::newRow("negativeNumber_shouldFail") << m_validCustomer << -1 << QDate::currentDate() << true << false;
}

void BillDAOTest::insertTest()
{
    QFETCH(Customer::Ptr, customer);
    QFETCH(int, number);
    QFETCH(QDate, date);
    QFETCH(bool, payed);
    QFETCH(bool, result);

    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setCustomer(customer);
    bill->setBillNumber(number);
    bill->setDate(date);
    bill->setPayed(payed);

    QCOMPARE(m_billDAO->create(bill), result);

    if(result) {
        QVERIFY(bill->id() >= 0);

        Bill::Ptr billFromData = m_billDAO->get(bill->id());
        QVERIFY(bill->equals(billFromData));
    }
}

void BillDAOTest::updateTest_data()
{
    QTest::addColumn<Customer::Ptr>("newCustomer");
    QTest::addColumn<int>("newNumber");
    QTest::addColumn<QDate>("newDate");
    QTest::addColumn<bool>("newPayed");
    QTest::addColumn<bool>("result");

    Customer::Ptr invalidCustomer = std::make_shared<Customer>();
    Customer::Ptr noCustomer = std::make_shared<Customer>();

    QTest::newRow("validData_shouldPass") << m_validCustomer << 1 << QDate::currentDate() << true << true;

    QTest::newRow("invalidCustomer_shouldFail") << invalidCustomer << 2 << QDate::currentDate() << true << false;
    QTest::newRow("noCustomer_shouldFail") << noCustomer << 3 << QDate::currentDate() << true << false;
    QTest::newRow("negativeNumber_shouldFail") << m_validCustomer << -1 << QDate::currentDate() << true << false;
}

void BillDAOTest::updateTest()
{
    QFETCH(Customer::Ptr, newCustomer);
    QFETCH(int, newNumber);
    QFETCH(QDate, newDate);
    QFETCH(bool, newPayed);
    QFETCH(bool, result);

    // PREPARE

    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setCustomer(m_validCustomer);
    bill->setBillNumber(1);
    bill->setDate(QDate::currentDate());
    bill->setPayed(true);

    QVERIFY(m_billDAO->create(bill));
    QVERIFY(bill->id() >= 0);

    // WHEN / THEN
    bill->setCustomer(newCustomer);
    bill->setBillNumber(newNumber);
    bill->setDate(newDate);
    bill->setPayed(newPayed);

    QCOMPARE(m_billDAO->update(bill), result);

    if(result) {
        Bill::Ptr billFromData = m_billDAO->get(bill->id());
        QVERIFY(bill->equals(billFromData));
    }
}

void BillDAOTest::updateWithInvalidIDTest()
{
    // PREPARE
    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setCustomer(m_validCustomer);
    bill->setBillNumber(1);
    bill->setDate(QDate::currentDate());
    bill->setPayed(true);

    // get not used id
    int id = 0;
    while(m_billDAO->get(id) != nullptr) {
        id++;
    }
    bill->setId(id);

    QCOMPARE(m_billDAO->update(bill), false);
}

void BillDAOTest::removeTestWithValidIDShouldPass()
{
    // PREPARE
    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setCustomer(m_validCustomer);
    bill->setBillNumber(1);
    bill->setDate(QDate::currentDate());
    bill->setPayed(true);

    QVERIFY(m_billDAO->create(bill));
    QVERIFY(bill->id() >= 0);

    int prevDataSetCount = m_billDAO->getAll().size();

    // WHEN / THEN
    QCOMPARE(m_billDAO->remove(bill), true);
    QCOMPARE(m_billDAO->getAll().size(), prevDataSetCount - 1);
}

void BillDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setCustomer(m_validCustomer);
    bill->setBillNumber(1);
    bill->setDate(QDate::currentDate());
    bill->setPayed(true);

    // get not used id
    int id = 0;
    while(m_billDAO->get(id) != nullptr) {
        id++;
    }
    bill->setId(id);

    // WHEN / THEN
    QCOMPARE(m_billDAO->remove(bill), false);
}

void BillDAOTest::getAllTest()
{
    int prevDataSetCount = m_billDAO->getAll().size();

    // PREPARE
    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setCustomer(m_validCustomer);
    bill->setBillNumber(1);
    bill->setDate(QDate::currentDate());
    bill->setPayed(true);

    // WHEN / THEN
    QVERIFY(m_billDAO->create(bill));
    QVERIFY(bill->id() >= 0);

    QCOMPARE(m_billDAO->getAll().size(), prevDataSetCount + 1);
}
