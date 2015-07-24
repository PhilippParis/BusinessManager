#include "billitemdaotest.h"

void BillItemDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_customerDAO = std::make_shared<DBCustomerDAO>(testDB, std::make_shared<CustomerValidator>());
    m_productDAO = std::make_shared<DBProductDAO>(testDB, std::make_shared<ProductValidator>());
    m_billItemDAO = std::make_shared<DBBillItemDAO>(testDB, std::make_shared<BillItemValidator>(), m_productDAO);

    // create dummy customer
    Customer::Ptr customer = std::make_shared<Customer>();
    customer->setCity("city");
    customer->setStreet("street");
    customer->setMail("mail");
    customer->setName("name");
    customer->setSurname("surname");
    customer->setTitle("title");
    customer->setOrganisation("org");
    m_customerDAO->create(customer);
    QVERIFY(customer->id() >= 0);

    // create dummy products
    m_invalidProduct = std::make_shared<Product>();
    m_nullProduct = nullptr;

    m_validProduct = std::make_shared<Product>();
    m_validProduct->setName("product");
    m_validProduct->setUnit("unit");

    m_productDAO->create(m_validProduct);
    QVERIFY(m_validProduct->id() >= 0);
}

void BillItemDAOTest::insertTest_data()
{
    QTest::addColumn<QMap<Product::Ptr, double>>("material");
    QTest::addColumn<QString>("desc");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<double>("cost");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("hours");
    QTest::addColumn<double>("wage");
    QTest::addColumn<double>("quantity");
    QTest::addColumn<bool>("result");

    // prepare materials
    QMap<Product::Ptr, double> validMaterial;
    validMaterial.insert(m_validProduct, 2.0);

    QMap<Product::Ptr, double> invalidMaterial1;
    invalidMaterial1.insert(m_invalidProduct, 2.0);

    QMap<Product::Ptr, double> invalidMaterial2;
    invalidMaterial2.insert(m_validProduct, -2.0);

    QMap<Product::Ptr, double> invalidMaterial3;
    invalidMaterial3.insert(m_nullProduct, 2.0);

    // create test data

    QTest::newRow("validData_shouldPass") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << true;
    QTest::newRow("descEmpty_shouldFail") << validMaterial << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("invalidBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("NoBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;

    QTest::newRow("invalidProduct_shouldFail") << invalidMaterial1 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("nullProduct_shouldFail") << invalidMaterial3 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
}

void BillItemDAOTest::insertTest()
{
    typedef QMap<Product::Ptr, double> MaterialMap;

    QFETCH(MaterialMap, material);
    QFETCH(QString, desc);
    QFETCH(QString, unit);
    QFETCH(double, cost);
    QFETCH(double, price);
    QFETCH(double, hours);
    QFETCH(double, wage);
    QFETCH(double, quantity);
    QFETCH(bool, result);

    BillItem::Ptr item = std::make_shared<BillItem>();
    item->setDescription(desc);
    item->setMaterialCost(cost);
    item->setPrice(price);
    item->setWorkingHours(hours);
    item->setWagePerHour(wage);
    item->setQuantity(quantity);
    item->setUnit(unit);

    QMap<Product::Ptr, double>::iterator it;
    for(it = material.begin(); it != material.end(); ++it) {
        item->addMaterial(it.key(), it.value());
    }

    try {
        m_billItemDAO->create(item);
        QVERIFY(item->id() >= 0);
        BillItem::Ptr itemFromData = m_billItemDAO->get(item->id());

        QVERIFY(item->equals(itemFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void BillItemDAOTest::updateTest_data()
{
    QTest::addColumn<QMap<Product::Ptr, double>>("material");
    QTest::addColumn<QString>("desc");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<double>("cost");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("hours");
    QTest::addColumn<double>("wage");
    QTest::addColumn<double>("quantity");
    QTest::addColumn<bool>("result");

    // create dummy invalid bills
    Bill::Ptr invalid_bill = std::make_shared<Bill>();
    Bill::Ptr no_bill = nullptr;

    // prepare materials
    QMap<Product::Ptr, double> validMaterial;
    validMaterial.insert(m_validProduct, 2.0);

    QMap<Product::Ptr, double> invalidMaterial1;
    invalidMaterial1.insert(m_invalidProduct, 2.0);

    QMap<Product::Ptr, double> invalidMaterial2;
    invalidMaterial2.insert(m_validProduct, -2.0);

    QMap<Product::Ptr, double> invalidMaterial3;
    invalidMaterial3.insert(m_nullProduct, 2.0);

    // create test data

    QTest::newRow("validData_shouldPass") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << true;
    QTest::newRow("descEmpty_shouldFail") << validMaterial << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("invalidBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("NoBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;

    QTest::newRow("invalidProduct_shouldFail") << invalidMaterial1 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("nullProduct_shouldFail") << invalidMaterial3 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
}

void BillItemDAOTest::updateTest()
{
    typedef QMap<Product::Ptr, double> MaterialMap;

    QFETCH(MaterialMap, material);
    QFETCH(QString, desc);
    QFETCH(QString, unit);
    QFETCH(double, cost);;
    QFETCH(double, price);
    QFETCH(double, hours);
    QFETCH(double, wage);
    QFETCH(double, quantity);
    QFETCH(bool, result);

    // PREPARE
    // create products
    Product::Ptr product1 = std::make_shared<Product>();
    product1->setName("product1");
    product1->setUnit("unit1");

    m_productDAO->create(product1);
    QVERIFY(product1->id() >= 0);

    Product::Ptr product2 = std::make_shared<Product>();
    product2->setName("product2");
    product2->setUnit("unit2");

    m_productDAO->create(product2);
    QVERIFY(product2->id() >= 0);

    // create bill item
    BillItem::Ptr item = std::make_shared<BillItem>();
    item->setDescription("desc");
    item->setMaterialCost(1.0);
    item->setPrice(5.0);
    item->setWorkingHours(10);
    item->setWagePerHour(1.3);
    item->setQuantity(5);
    item->setUnit("unit");
    item->addMaterial(product1, 1.2);
    item->addMaterial(product2, 2.4);

    m_billItemDAO->create(item);
    QVERIFY(item->id() >= 0);

    // WHEN / THEN
    item->setDescription(desc);
    item->setMaterialCost(cost);
    item->setPrice(price);
    item->setWorkingHours(hours);
    item->setWagePerHour(wage);
    item->setQuantity(quantity);
    item->setUnit(unit);

    QMap<Product::Ptr, double>::iterator it;
    for(it = material.begin(); it != material.end(); ++it) {
        item->addMaterial(it.key(), it.value());
    }

    try {
        m_billItemDAO->update(item);
        BillItem::Ptr itemFromData = m_billItemDAO->get(item->id());
        QVERIFY(item->equals(itemFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void BillItemDAOTest::updateWithInvalidIDTest()
{
    BillItem::Ptr item = std::make_shared<BillItem>();
    item->setDescription("desc");
    item->setMaterialCost(1.0);
    item->setPrice(5.0);
    item->setWorkingHours(10);
    item->setWagePerHour(1.3);
    item->setQuantity(5);
    item->setUnit("unit");

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_billItemDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    item->setId(id);

    try {
        m_billItemDAO->update(item);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void BillItemDAOTest::removeTestWithValidIDShouldPass()
{
    // PREPARE
    BillItem::Ptr item = std::make_shared<BillItem>();
    item->setDescription("desc");
    item->setMaterialCost(1.0);
    item->setPrice(5.0);
    item->setWorkingHours(10);
    item->setWagePerHour(1.3);
    item->setQuantity(5);
    item->setUnit("unit");

    m_billItemDAO->create(item);
    QVERIFY(item->id() >= 0);

    int prevDataSetCount = m_billItemDAO->getAll().size();

    // WHEN / THEN
    m_billItemDAO->remove(item);
    QCOMPARE(m_billItemDAO->getAll().size(), prevDataSetCount - 1);
}

void BillItemDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    BillItem::Ptr item = std::make_shared<BillItem>();
    // get not used id
    int id = 0;
    try {
        while(true) {
            m_billItemDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    item->setId(id);

    // WHEN / THEN
    try {
        m_billItemDAO->remove(item);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void BillItemDAOTest::getAllTest()
{
    int prevDataSetCount = m_billItemDAO->getAll().size();

    // PREPARE
    BillItem::Ptr item = std::make_shared<BillItem>();
    item->setDescription("desc");
    item->setMaterialCost(1.0);
    item->setPrice(5.0);
    item->setWorkingHours(10);
    item->setWagePerHour(1.3);
    item->setQuantity(5);
    item->setUnit("unit");

    m_billItemDAO->create(item);
    QVERIFY(item->id() >= 0);

    QCOMPARE(m_billItemDAO->getAll().size(), prevDataSetCount + 1);
}

