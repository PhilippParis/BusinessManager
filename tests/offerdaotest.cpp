#include "offerdaotest.h"

void OfferDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_materialDAO = std::make_shared<DBMaterialDAO>(testDB, std::make_shared<MaterialValidator>());
    m_offerItemDAO = std::make_shared<DBOfferItemDAO>(testDB, std::make_shared<BillItemValidator>(), m_materialDAO);
    m_customerDAO = std::make_shared<DBCustomerDAO>(testDB, std::make_shared<CustomerValidator>());
    m_offerDAO = std::make_shared<DBOfferDAO>(testDB, std::make_shared<OfferValidator>(), m_offerItemDAO, m_customerDAO);

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

    // create dummy valid offer item
    m_validOfferItem = std::make_shared<BillItem>();
    m_validOfferItem->setDescription("item");
    m_validOfferItem->setMaterialNetCost(Decimal::fromValue(10.0));
    m_validOfferItem->setPrice(Decimal::fromValue(200.0));
    m_validOfferItem->setQuantity(4.0);
    m_validOfferItem->setUnit("Stk.");
    m_validOfferItem->setWagePerHour(Decimal::fromValue(10.0));
    m_validOfferItem->setWorkingHours(1.0);
    m_validOfferItem->setMaterialOverhead(0.05);
    m_validOfferItem->setFactoryOverhead(0.05);
    m_validOfferItem->setProfit(0.2);
    m_validOfferItem->setCashback(0.02);
    m_validOfferItem->setTaxRate(0.2);

    m_offerItemDAO->create(m_validOfferItem);
    QVERIFY(m_validOfferItem->id() >= 0);
}

void OfferDAOTest::insertTest_data()
{
    typedef QList<BillItem::Ptr> ItemList;

    QTest::addColumn<ItemList>("items");
    QTest::addColumn<Customer::Ptr>("customer");
    QTest::addColumn<QDate>("date");
    QTest::addColumn<bool>("result");

    Customer::Ptr invalidCustomer = std::make_shared<Customer>();
    Customer::Ptr noCustomer = nullptr;

    BillItem::Ptr invalidOfferItem = std::make_shared<BillItem>();
    BillItem::Ptr nullOfferItem = nullptr;

    // prepare items
    QList<BillItem::Ptr> validOfferItems;
    validOfferItems.append(m_validOfferItem);

    QList<BillItem::Ptr> invalidOfferItems1;
    invalidOfferItems1.append(invalidOfferItem);

    QList<BillItem::Ptr> invalidOfferItems2;
    invalidOfferItems2.append(nullOfferItem);

    QTest::newRow("validData_shouldPass") << validOfferItems << m_validCustomer << QDate::currentDate() << true;

    QTest::newRow("invalidCustomer_shouldFail") << validOfferItems << invalidCustomer << QDate::currentDate() << false;
    QTest::newRow("noCustomer_shouldFail") << validOfferItems << noCustomer << QDate::currentDate() << false;

    QTest::newRow("invalidItem_shouldFail") << invalidOfferItems1 << m_validCustomer << QDate::currentDate() << false;
    QTest::newRow("nullItem_shouldFail") << invalidOfferItems2 << m_validCustomer << QDate::currentDate() << false;
}

void OfferDAOTest::insertTest()
{
    QFETCH(QList<BillItem::Ptr>, items);
    QFETCH(Customer::Ptr, customer);
    QFETCH(QDate, date);
    QFETCH(bool, result);

    Offer::Ptr offer = std::make_shared<Offer>();
    offer->setCustomer(customer);
    offer->setDate(date);
    offer->setItems(items);

    try {
        m_offerDAO->create(offer);
        QVERIFY(offer->id() >= 0);

        Offer::Ptr offerFromData = m_offerDAO->get(offer->id());
        QVERIFY(offer->equals(offerFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void OfferDAOTest::updateTest_data()
{
    typedef QList<BillItem::Ptr> ItemList;

    QTest::addColumn<ItemList>("items");
    QTest::addColumn<Customer::Ptr>("customer");
    QTest::addColumn<QDate>("date");
    QTest::addColumn<bool>("result");

    Customer::Ptr invalidCustomer = std::make_shared<Customer>();
    Customer::Ptr noCustomer = nullptr;

    BillItem::Ptr invalidOfferItem = std::make_shared<BillItem>();
    BillItem::Ptr nullOfferItem = nullptr;

    // prepare items
    QList<BillItem::Ptr> validOfferItems;
    validOfferItems.append(m_validOfferItem);

    QList<BillItem::Ptr> invalidOfferItems1;
    invalidOfferItems1.append(invalidOfferItem);

    QList<BillItem::Ptr> invalidOfferItems2;
    invalidOfferItems2.append(nullOfferItem);

    QTest::newRow("validData_shouldPass") << validOfferItems << m_validCustomer << QDate::currentDate() << true;

    QTest::newRow("invalidCustomer_shouldFail") << validOfferItems << invalidCustomer << QDate::currentDate() << false;
    QTest::newRow("noCustomer_shouldFail") << validOfferItems << noCustomer << QDate::currentDate() << false;

    QTest::newRow("invalidItem_shouldFail") << invalidOfferItems1 << m_validCustomer << QDate::currentDate() << false;
    QTest::newRow("nullItem_shouldFail") << invalidOfferItems2 << m_validCustomer << QDate::currentDate() << false;
}

void OfferDAOTest::updateTest()
{
    QFETCH(QList<BillItem::Ptr>, items);
    QFETCH(Customer::Ptr, customer);
    QFETCH(QDate, date);
    QFETCH(bool, result);

    // PREPARE
    QList<BillItem::Ptr> validOfferItems;
    validOfferItems.append(m_validOfferItem);
    validOfferItems.append(m_validOfferItem);

    Offer::Ptr offer = std::make_shared<Offer>();
    offer->setCustomer(m_validCustomer);
    offer->setDate(QDate::currentDate());
    offer->setItems(validOfferItems);

    m_offerDAO->create(offer);
    QVERIFY(offer->id() >= 0);

    // WHEN / THEN
    offer->setCustomer(customer);
    offer->setDate(date);
    offer->setItems(items);

    try {
        m_offerDAO->update(offer);
        Offer::Ptr offerFromData = m_offerDAO->get(offer->id());
        QVERIFY(offer->equals(offerFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void OfferDAOTest::updateWithInvalidIDTest()
{
    // PREPARE
    Offer::Ptr offer = std::make_shared<Offer>();
    offer->setCustomer(m_validCustomer);
    offer->setDate(QDate::currentDate());

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_offerDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }

    offer->setId(id);

    try {
        m_offerDAO->update(offer);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void OfferDAOTest::removeTestWithValidIDShouldPass()
{
    // PREPARE
    Offer::Ptr offer = std::make_shared<Offer>();
    offer->setCustomer(m_validCustomer);
    offer->setDate(QDate::currentDate());

    m_offerDAO->create(offer);
    QVERIFY(offer->id() >= 0);

    int prevDataSetCount = m_offerDAO->getAll().size();

    // WHEN / THEN
    m_offerDAO->remove(offer);
    QCOMPARE(m_offerDAO->getAll().size(), prevDataSetCount - 1);
}

void OfferDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    Offer::Ptr offer = std::make_shared<Offer>();

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_offerDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    offer->setId(id);

    // WHEN / THEN
    try {
        m_offerDAO->remove(offer);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void OfferDAOTest::getAllTest()
{
    int prevDataSetCount = m_offerDAO->getAll().size();

    // PREPARE
    Offer::Ptr offer = std::make_shared<Offer>();
    offer->setCustomer(m_validCustomer);
    offer->setDate(QDate::currentDate());

    // WHEN / THEN
    m_offerDAO->create(offer);
    QVERIFY(offer->id() >= 0);

    QCOMPARE(m_offerDAO->getAll().size(), prevDataSetCount + 1);
}
