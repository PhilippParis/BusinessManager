#include "templatedaotest.h"

void TemplateDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_productDAO = std::make_shared<DBProductDAO>(testDB, std::make_shared<ProductValidator>());
    m_templateDAO = std::make_shared<DBTemplateDAO>(testDB, std::make_shared<TemplateValidator>(), m_productDAO);

    // create dummy products
    m_invalidProduct = std::make_shared<Product>();
    m_nullProduct = nullptr;

    m_validProduct = std::make_shared<Product>();
    m_validProduct->setName("product");
    m_validProduct->setUnit("unit");

    m_productDAO->create(m_validProduct);
    QVERIFY(m_validProduct->id() >= 0);
}

void TemplateDAOTest::insertTest_data()
{
    QTest::addColumn<QMap<Product::Ptr, double>>("material");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("org");
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("desc");
    QTest::addColumn<QString>("itemDesc");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<double>("hours");
    QTest::addColumn<double>("price");
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

    QTest::newRow("validData_shouldPass") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << true;
    QTest::newRow("itemDescEmpty_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << ""<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "" << 10.0 << 500.0 << false;
    QTest::newRow("negativePrice_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << -500.0 << false;
    QTest::newRow("negativeHourse_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << -10.0 << 500.0 << false;

    QTest::newRow("invalidProduct_shouldFail") << invalidMaterial1 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("nullProduct_shouldFail") << invalidMaterial3 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
}

void TemplateDAOTest::insertTest()
{
    typedef QMap<Product::Ptr, double> MaterialMap;

    QFETCH(MaterialMap, material);
    QFETCH(QString, name);
    QFETCH(QString, org);
    QFETCH(QString, type);
    QFETCH(QString, desc);
    QFETCH(QString, itemDesc);
    QFETCH(QString, unit);
    QFETCH(double, hours);
    QFETCH(double, price);
    QFETCH(bool, result);

    Template::Ptr templ = std::make_shared<Template>();
    templ->setName(desc);
    templ->setOrganisation(org);
    templ->setType(type);
    templ->setDesc(desc);
    templ->setItemDesc(itemDesc);
    templ->setUnit(unit);
    templ->setWorkingHours(hours);
    templ->setPrice(price);
    templ->setMaterial(material);

    try {
        m_templateDAO->create(templ);
        QVERIFY(templ->id() >= 0);
        Template::Ptr templateFromData = m_templateDAO->get(templ->id());

        QVERIFY(templ->equals(templateFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void TemplateDAOTest::updateTest_data()
{
    QTest::addColumn<QMap<Product::Ptr, double>>("material");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("org");
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("desc");
    QTest::addColumn<QString>("itemDesc");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<double>("hours");
    QTest::addColumn<double>("price");
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

    QTest::newRow("validData_shouldPass") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << true;
    QTest::newRow("itemDescEmpty_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << ""<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "" << 10.0 << 500.0 << false;
    QTest::newRow("negativePrice_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << -500.0 << false;
    QTest::newRow("negativeHourse_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << -10.0 << 500.0 << false;

    QTest::newRow("invalidProduct_shouldFail") << invalidMaterial1 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("nullProduct_shouldFail") << invalidMaterial3 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
}

void TemplateDAOTest::updateTest()
{
    typedef QMap<Product::Ptr, double> MaterialMap;

    QFETCH(MaterialMap, material);
    QFETCH(QString, name);
    QFETCH(QString, org);
    QFETCH(QString, type);
    QFETCH(QString, desc);
    QFETCH(QString, itemDesc);
    QFETCH(QString, unit);
    QFETCH(double, hours);
    QFETCH(double, price);
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

    // create valid template
    Template::Ptr templ = std::make_shared<Template>();
    templ->setName("desc");
    templ->setOrganisation("org");
    templ->setType("type");
    templ->setDesc("desc");
    templ->setItemDesc("itemDesc");
    templ->setUnit("unit");
    templ->setWorkingHours(1.0);
    templ->setPrice(10.0);

    QMap<Product::Ptr, double> m;
    m.insert(product1, 1.2);
    m.insert(product2, 2.4);
    templ->setMaterial(m);

    m_templateDAO->create(templ);
    QVERIFY(templ->id() >= 0);

    // WHEN / THEN
    templ->setName(desc);
    templ->setOrganisation(org);
    templ->setType(type);
    templ->setDesc(desc);
    templ->setItemDesc(itemDesc);
    templ->setUnit(unit);
    templ->setWorkingHours(hours);
    templ->setPrice(price);
    templ->setMaterial(material);

    try {
        m_templateDAO->update(templ);
        Template::Ptr templFromData = m_templateDAO->get(templ->id());
        QVERIFY(templ->equals(templFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void TemplateDAOTest::updateWithInvalidIDTest()
{
    Template::Ptr templ = std::make_shared<Template>();
    templ->setName("desc");
    templ->setOrganisation("org");
    templ->setType("type");
    templ->setDesc("desc");
    templ->setItemDesc("itemDesc");
    templ->setUnit("unit");
    templ->setWorkingHours(1.0);
    templ->setPrice(10.0);

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_templateDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    templ->setId(id);

    try {
        m_templateDAO->update(templ);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void TemplateDAOTest::removeTestWithValidIDShouldPass()
{
    // create valid template
    Template::Ptr templ = std::make_shared<Template>();
    templ->setName("desc");
    templ->setOrganisation("org");
    templ->setType("type");
    templ->setDesc("desc");
    templ->setItemDesc("itemDesc");
    templ->setUnit("unit");
    templ->setWorkingHours(1.0);
    templ->setPrice(10.0);

    m_templateDAO->create(templ);
    QVERIFY(templ->id() >= 0);

    int prevDataSetCount = m_templateDAO->getAll().size();

    // WHEN / THEN
    m_templateDAO->remove(templ);
    QCOMPARE(m_templateDAO->getAll().size(), prevDataSetCount - 1);
}

void TemplateDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    Template::Ptr templ = std::make_shared<Template>();
    // get not used id
    int id = 0;
    try {
        while(true) {
            m_templateDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    templ->setId(id);

    // WHEN / THEN
    try {
        m_templateDAO->remove(templ);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void TemplateDAOTest::getAllTest()
{
    int prevDataSetCount = m_templateDAO->getAll().size();

    // PREPARE
    // create valid template
    Template::Ptr templ = std::make_shared<Template>();
    templ->setName("desc");
    templ->setOrganisation("org");
    templ->setType("type");
    templ->setDesc("desc");
    templ->setItemDesc("itemDesc");
    templ->setUnit("unit");
    templ->setWorkingHours(1.0);
    templ->setPrice(10.0);

    m_templateDAO->create(templ);
    QVERIFY(templ->id() >= 0);

    QCOMPARE(m_templateDAO->getAll().size(), prevDataSetCount + 1);
}
