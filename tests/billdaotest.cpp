#include "billdaotest.h"

void BillDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    DiscountDAO::Ptr discountDAO = std::make_shared<DBDiscountDAO>(testDB, std::make_shared<DiscountValidator>());

    m_materialDAO = std::make_shared<DBMaterialDAO>(testDB, std::make_shared<MaterialValidator>());
    m_billItemDAO = std::make_shared<DBBillItemDAO>(testDB, std::make_shared<BillItemValidator>(), m_materialDAO);
    m_customerDAO = std::make_shared<DBCustomerDAO>(testDB, std::make_shared<CustomerValidator>());
    m_billDAO = std::make_shared<DBBillDAO>(testDB, std::make_shared<BillValidator>(), m_customerDAO, m_billItemDAO, discountDAO);

    // create dummy valid customer
    m_validCustomer = std::make_shared<Customer>();
    m_validCustomer->setTitle("title");
    m_validCustomer->setName("name");
    m_validCustomer->setSurname("surname");
    m_validCustomer->setOrganisation("org");
    m_validCustomer->setCity("city");
    m_validCustomer->setStreet("street");
    m_validCustomer->setMail("mail");

    m_customerDAO->create(m_validCustomer);
    QVERIFY(m_validCustomer->id() >= 0);

    // create dummy valid bill item
    m_validBillItem = std::make_shared<BillItem>();
    m_validBillItem->setDescription("item");
    m_validBillItem->setMaterialCost(10.0);
    m_validBillItem->setPrice(200.0);
    m_validBillItem->setQuantity(4.0);
    m_validBillItem->setUnit("Stk.");
    m_validBillItem->setWagePerHour(10.0);
    m_validBillItem->setWorkingHours(1.0);

    m_billItemDAO->create(m_validBillItem);
    QVERIFY(m_validBillItem->id() >= 0);
}

void BillDAOTest::insertTest_data()
{
    typedef QList<BillItem::Ptr> ItemList;

    QTest::addColumn<ItemList>("items");
    QTest::addColumn<Customer::Ptr>("customer");
    QTest::addColumn<int>("number");
    QTest::addColumn<QDate>("date");
    QTest::addColumn<bool>("payed");
    QTest::addColumn<bool>("result");

    Customer::Ptr invalidCustomer = std::make_shared<Customer>();
    Customer::Ptr noCustomer = nullptr;

    BillItem::Ptr invalidBillItem = std::make_shared<BillItem>();
    BillItem::Ptr nullBillItem = nullptr;

    // prepare items
    QList<BillItem::Ptr> validBillItems;
    validBillItems.append(m_validBillItem);

    QList<BillItem::Ptr> invalidBillItems1;
    invalidBillItems1.append(invalidBillItem);

    QList<BillItem::Ptr> invalidBillItems2;
    invalidBillItems2.append(nullBillItem);

    QTest::newRow("validData_shouldPass") << validBillItems << m_validCustomer << 1 << QDate::currentDate() << true << true;

    QTest::newRow("invalidCustomer_shouldFail") << validBillItems << invalidCustomer << 2 << QDate::currentDate() << true << false;
    QTest::newRow("noCustomer_shouldFail") << validBillItems << noCustomer << 3 << QDate::currentDate() << true << false;
    QTest::newRow("negativeNumber_shouldFail") << validBillItems << m_validCustomer << -1 << QDate::currentDate() << true << false;

    QTest::newRow("invalidItem_shouldFail") << invalidBillItems1 << m_validCustomer << 1 << QDate::currentDate() << true << false;
    QTest::newRow("nullItem_shouldFail") << invalidBillItems2 << m_validCustomer << 1 << QDate::currentDate() << true << false;
}

void BillDAOTest::insertTest()
{
    QFETCH(QList<BillItem::Ptr>, items);
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
    bill->setItems(items);

    try {
        m_billDAO->create(bill);
        QVERIFY(bill->id() >= 0);

        Bill::Ptr billFromData = m_billDAO->get(bill->id());
        QVERIFY(bill->equals(billFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void BillDAOTest::updateTest_data()
{
    typedef QList<BillItem::Ptr> ItemList;

    QTest::addColumn<ItemList>("items");
    QTest::addColumn<Customer::Ptr>("customer");
    QTest::addColumn<int>("number");
    QTest::addColumn<QDate>("date");
    QTest::addColumn<bool>("payed");
    QTest::addColumn<bool>("result");

    Customer::Ptr invalidCustomer = std::make_shared<Customer>();
    Customer::Ptr noCustomer = nullptr;

    BillItem::Ptr invalidBillItem = std::make_shared<BillItem>();
    BillItem::Ptr nullBillItem = nullptr;

    // prepare items
    QList<BillItem::Ptr> validBillItems;
    validBillItems.append(m_validBillItem);

    QList<BillItem::Ptr> invalidBillItems1;
    invalidBillItems1.append(invalidBillItem);

    QList<BillItem::Ptr> invalidBillItems2;
    invalidBillItems2.append(nullBillItem);

    QTest::newRow("validData_shouldPass") << validBillItems << m_validCustomer << 1 << QDate::currentDate() << true << true;

    QTest::newRow("invalidCustomer_shouldFail") << validBillItems << invalidCustomer << 2 << QDate::currentDate() << true << false;
    QTest::newRow("noCustomer_shouldFail") << validBillItems << noCustomer << 3 << QDate::currentDate() << true << false;
    QTest::newRow("negativeNumber_shouldFail") << validBillItems << m_validCustomer << -1 << QDate::currentDate() << true << false;

    QTest::newRow("invalidItem_shouldFail") << invalidBillItems1 << m_validCustomer << 1 << QDate::currentDate() << true << false;
    QTest::newRow("nullItem_shouldFail") << invalidBillItems2 << m_validCustomer << 1 << QDate::currentDate() << true << false;
}

void BillDAOTest::updateTest()
{
    QFETCH(QList<BillItem::Ptr>, items);
    QFETCH(Customer::Ptr, customer);
    QFETCH(int, number);
    QFETCH(QDate, date);
    QFETCH(bool, payed);
    QFETCH(bool, result);

    // PREPARE
    QList<BillItem::Ptr> validBillItems;
    validBillItems.append(m_validBillItem);
    validBillItems.append(m_validBillItem);

    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setCustomer(m_validCustomer);
    bill->setBillNumber(1);
    bill->setDate(QDate::currentDate());
    bill->setPayed(true);
    bill->setItems(validBillItems);

    m_billDAO->create(bill);
    QVERIFY(bill->id() >= 0);

    // WHEN / THEN
    bill->setCustomer(customer);
    bill->setBillNumber(number);
    bill->setDate(date);
    bill->setPayed(payed);
    bill->setItems(items);

    try {
        m_billDAO->update(bill);
        Bill::Ptr billFromData = m_billDAO->get(bill->id());
        QVERIFY(bill->equals(billFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
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
    try {
        while(true) {
            m_billDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }

    bill->setId(id);

    try {
        m_billDAO->update(bill);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void BillDAOTest::removeTestWithValidIDShouldPass()
{
    // PREPARE
    Bill::Ptr bill = std::make_shared<Bill>();
    bill->setCustomer(m_validCustomer);
    bill->setBillNumber(1);
    bill->setDate(QDate::currentDate());
    bill->setPayed(true);

    m_billDAO->create(bill);
    QVERIFY(bill->id() >= 0);

    int prevDataSetCount = m_billDAO->getAll().size();

    // WHEN / THEN
    m_billDAO->remove(bill);
    QCOMPARE(m_billDAO->getAll().size(), prevDataSetCount - 1);
}

void BillDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    Bill::Ptr bill = std::make_shared<Bill>();

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_billDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    bill->setId(id);

    // WHEN / THEN
    try {
        m_billDAO->remove(bill);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
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
    m_billDAO->create(bill);
    QVERIFY(bill->id() >= 0);

    QCOMPARE(m_billDAO->getAll().size(), prevDataSetCount + 1);
}
