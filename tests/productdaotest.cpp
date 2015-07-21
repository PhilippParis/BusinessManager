#include "productdaotest.h"

void ProductDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_productDAO = std::make_shared<DBProductDAO>(testDB, std::make_shared<ProductValidator>());
}

void ProductDAOTest::insertTest_data()
{
    QTest::addColumn<int>("stock");
    QTest::addColumn<double>("cost");
    QTest::addColumn<double>("price");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<QString>("desc");
    QTest::addColumn<bool>("result");

    QTest::newRow("validData_shouldPass") << 1 << 1.0 << 2.0 << "name" << "type" << "unit" << "desc" << true;
    QTest::newRow("negativeCost_shouldFail") << 1 << -1.0 << 2.0 << "name" << "type" << "unit" << "desc" << false;
    QTest::newRow("negativePrice_shouldFail") << 1 << 1.0 << -2.0 << "name" << "type" << "unit" << "desc" << false;
    QTest::newRow("emptyName_shouldFail") << 1 << 1.0 << 2.0 << "" << "type" << "unit" << "desc" << false;
    QTest::newRow("emptyUnit_shouldFail") << 1 << 1.0 << 2.0 << "name" << "type" << "" << "desc" << false;
}

void ProductDAOTest::insertTest()
{
    QFETCH(int, stock);
    QFETCH(double, cost);
    QFETCH(double, price);
    QFETCH(QString, name);
    QFETCH(QString, type);
    QFETCH(QString, unit);
    QFETCH(QString, desc);
    QFETCH(bool, result);

    Product::Ptr product = std::make_shared<Product>();
    product->setName(name);
    product->setCostPerUnit(cost);
    product->setPricePerUnit(price);
    product->setName(name);
    product->setType(type);
    product->setUnit(unit);
    product->setDesc(desc);

    try {
        m_productDAO->create(product);
        QVERIFY(product->id() >= 0);

        Product::Ptr productFromData = m_productDAO->get(product->id());
        QVERIFY(product->equals(productFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void ProductDAOTest::updateTest_data()
{
    QTest::addColumn<int>("stock");
    QTest::addColumn<double>("cost");
    QTest::addColumn<double>("price");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<QString>("desc");
    QTest::addColumn<bool>("result");

    QTest::newRow("validData_shouldPass") << 1 << 1.0 << 2.0 << "name" << "type" << "unit" << "desc" << true;
    QTest::newRow("negativeCost_shouldFail") << 1 << -1.0 << 2.0 << "name" << "type" << "unit" << "desc" << false;
    QTest::newRow("negativePrice_shouldFail") << 1 << 1.0 << -2.0 << "name" << "type" << "unit" << "desc" << false;
    QTest::newRow("emptyName_shouldFail") << 1 << 1.0 << 2.0 << "" << "type" << "unit" << "desc" << false;
    QTest::newRow("emptyUnit_shouldFail") << 1 << 1.0 << 2.0 << "name" << "type" << "" << "desc" << false;
}

void ProductDAOTest::updateTest()
{
    QFETCH(int, stock);
    QFETCH(double, cost);
    QFETCH(double, price);
    QFETCH(QString, name);
    QFETCH(QString, type);
    QFETCH(QString, unit);
    QFETCH(QString, desc);
    QFETCH(bool, result);

    Product::Ptr product = std::make_shared<Product>();
    product->setName("name");
    product->setCostPerUnit(1.0);
    product->setPricePerUnit(2.0);
    product->setName("name");
    product->setType("type");
    product->setUnit("unit");
    product->setDesc("desc");

    m_productDAO->create(product);
    QVERIFY(product->id() >= 0);
    Product::Ptr productFromData = m_productDAO->get(product->id());
    QVERIFY(product->equals(productFromData));

    product->setName(name);
    product->setCostPerUnit(cost);
    product->setPricePerUnit(price);
    product->setName(name);
    product->setType(type);
    product->setUnit(unit);
    product->setDesc(desc);

    try {
        m_productDAO->update(product);
        productFromData = m_productDAO->get(product->id());
        QVERIFY(product->equals(productFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void ProductDAOTest::updateWithInvalidIDTest()
{
    // PREPARE
    Product::Ptr product = std::make_shared<Product>();
    product->setName("name");
    product->setCostPerUnit(1.0);
    product->setPricePerUnit(2.0);
    product->setName("name");
    product->setType("type");
    product->setUnit("unit");
    product->setDesc("desc");

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_productDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    product->setId(id);

    try {
        m_productDAO->update(product);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void ProductDAOTest::removeTestWithValidIDShouldPass()
{
    // PREPARE
    Product::Ptr product = std::make_shared<Product>();
    product->setName("name");
    product->setCostPerUnit(1.0);
    product->setPricePerUnit(2.0);
    product->setName("name");
    product->setType("type");
    product->setUnit("unit");
    product->setDesc("desc");

    m_productDAO->create(product);
    QVERIFY(product->id() >= 0);

    int prevDataSetCount = m_productDAO->getAll().size();

    // WHEN / THEN
    m_productDAO->remove(product);
    QCOMPARE(m_productDAO->getAll().size(), prevDataSetCount - 1);
}

void ProductDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    Product::Ptr product = std::make_shared<Product>();

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_productDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    product->setId(id);

    // WHEN / THEN
    try {
        m_productDAO->remove(product);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void ProductDAOTest::getAllTest()
{
    int prevDataSetCount = m_productDAO->getAll().size();

    // PREPARE
    Product::Ptr product = std::make_shared<Product>();
    product->setName("name");
    product->setCostPerUnit(1.0);
    product->setPricePerUnit(2.0);
    product->setName("name");
    product->setType("type");
    product->setUnit("unit");
    product->setDesc("desc");

    // WHEN / THEN
    m_productDAO->create(product);
    QVERIFY(product->id() >= 0);

    QCOMPARE(m_productDAO->getAll().size(), prevDataSetCount + 1);
}
