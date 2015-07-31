#include "billitemdaotest.h"

void BillItemDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_materialDAO = std::make_shared<DBMaterialDAO>(testDB, std::make_shared<MaterialValidator>());
    m_billItemDAO = std::make_shared<DBBillItemDAO>(testDB, std::make_shared<BillItemValidator>(), m_materialDAO);

    // create dummy materials
    m_invalidMaterial = std::make_shared<Material>();
    m_nullMaterial = nullptr;

    m_validMaterial = std::make_shared<Material>();
    m_validMaterial->setName("material");
    m_validMaterial->setUnit("unit");

    m_materialDAO->create(m_validMaterial);
    QVERIFY(m_validMaterial->id() >= 0);
}

void BillItemDAOTest::insertTest_data()
{
    QTest::addColumn<QMap<Material::Ptr, double>>("material");
    QTest::addColumn<QString>("desc");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<double>("cost");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("hours");
    QTest::addColumn<double>("wage");
    QTest::addColumn<double>("quantity");
    QTest::addColumn<bool>("result");

    // prepare materials
    QMap<Material::Ptr, double> validMaterial;
    validMaterial.insert(m_validMaterial, 2.0);

    QMap<Material::Ptr, double> invalidMaterial1;
    invalidMaterial1.insert(m_invalidMaterial, 2.0);

    QMap<Material::Ptr, double> invalidMaterial2;
    invalidMaterial2.insert(m_validMaterial, -2.0);

    QMap<Material::Ptr, double> invalidMaterial3;
    invalidMaterial3.insert(m_nullMaterial, 2.0);

    // create test data

    QTest::newRow("validData_shouldPass") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << true;
    QTest::newRow("descEmpty_shouldFail") << validMaterial << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("invalidBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("NoBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;

    QTest::newRow("invalidMaterial_shouldFail") << invalidMaterial1 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("nullMaterial_shouldFail") << invalidMaterial3 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
}

void BillItemDAOTest::insertTest()
{
    typedef QMap<Material::Ptr, double> MaterialMap;

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

    item->setMaterial(material);

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
    QTest::addColumn<QMap<Material::Ptr, double>>("material");
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
    QMap<Material::Ptr, double> validMaterial;
    validMaterial.insert(m_validMaterial, 2.0);

    QMap<Material::Ptr, double> invalidMaterial1;
    invalidMaterial1.insert(m_invalidMaterial, 2.0);

    QMap<Material::Ptr, double> invalidMaterial2;
    invalidMaterial2.insert(m_validMaterial, -2.0);

    QMap<Material::Ptr, double> invalidMaterial3;
    invalidMaterial3.insert(m_nullMaterial, 2.0);

    // create test data

    QTest::newRow("validData_shouldPass") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << true;
    QTest::newRow("descEmpty_shouldFail") << validMaterial << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("invalidBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("NoBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;

    QTest::newRow("invalidMaterial_shouldFail") << invalidMaterial1 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
    QTest::newRow("nullMaterial_shouldFail") << invalidMaterial3 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << false;
}

void BillItemDAOTest::updateTest()
{
    typedef QMap<Material::Ptr, double> MaterialMap;

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
    // create Materials
    Material::Ptr material1 = std::make_shared<Material>();
    material1->setName("material1");
    material1->setUnit("unit1");

    m_materialDAO->create(material1);
    QVERIFY(material1->id() >= 0);

    Material::Ptr material2 = std::make_shared<Material>();
    material2->setName("material2");
    material2->setUnit("unit2");

    m_materialDAO->create(material2);
    QVERIFY(material2->id() >= 0);

    // create bill item
    BillItem::Ptr item = std::make_shared<BillItem>();
    item->setDescription("desc");
    item->setMaterialCost(1.0);
    item->setPrice(5.0);
    item->setWorkingHours(10);
    item->setWagePerHour(1.3);
    item->setQuantity(5);
    item->setUnit("unit");

    QMap<Material::Ptr, double> m;
    m.insert(material1, 1.2);
    m.insert(material2, 2.4);
    item->setMaterial(m);

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

    item->setMaterial(material);

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

