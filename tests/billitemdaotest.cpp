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
    QTest::addColumn<double>("materialOverhead");
    QTest::addColumn<double>("factoryOverhead");
    QTest::addColumn<double>("profit");
    QTest::addColumn<double>("cashback");
    QTest::addColumn<double>("tax");
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

    QTest::newRow("validData_shouldPass") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << true;
    QTest::newRow("descEmpty_shouldFail") << validMaterial << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("invalidBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("NoBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;


    QTest::newRow("matOverheadInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << -0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("matOverheadInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 1.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("facOverheadInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << -0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("facOverheadInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 1.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("profitInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << -0.2 << 0.02 << 0.2 << false;
    QTest::newRow("profitInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 1.2 << 0.02 << 0.2 << false;
    QTest::newRow("cashbackInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << -0.02 << 0.2 << false;
    QTest::newRow("cashbackInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 1.02 << 0.2 << false;
    QTest::newRow("taxInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << -0.2 << false;
    QTest::newRow("taxInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 1.2 << false;

    QTest::newRow("invalidMaterial_shouldFail") << invalidMaterial1 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("nullMaterial_shouldFail") << invalidMaterial3 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
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
    QFETCH(double, materialOverhead);
    QFETCH(double, factoryOverhead);
    QFETCH(double, profit);
    QFETCH(double, cashback);
    QFETCH(double, tax);
    QFETCH(bool, result);

    BillItem::Ptr item = std::make_shared<BillItem>();
    item->setDescription(desc);
    item->setMaterialCost(Decimal::fromValue(cost));
    item->setPrice(Decimal::fromValue(price));
    item->setWorkingHours(hours);
    item->setWagePerHour(Decimal::fromValue(wage));
    item->setQuantity(quantity);
    item->setUnit(unit);
    item->setMaterialOverhead(materialOverhead);
    item->setFactoryOverhead(factoryOverhead);
    item->setProfit(profit);
    item->setCashback(cashback);
    item->setTaxRate(tax);

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
    QTest::addColumn<double>("materialOverhead");
    QTest::addColumn<double>("factoryOverhead");
    QTest::addColumn<double>("profit");
    QTest::addColumn<double>("cashback");
    QTest::addColumn<double>("tax");
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

    QTest::newRow("validData_shouldPass") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << true;
    QTest::newRow("descEmpty_shouldFail") << validMaterial << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("invalidBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("NoBill_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;


    QTest::newRow("matOverheadInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << -0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("matOverheadInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 1.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("facOverheadInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << -0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("facOverheadInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 1.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("profitInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << -0.2 << 0.02 << 0.2 << false;
    QTest::newRow("profitInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 1.2 << 0.02 << 0.2 << false;
    QTest::newRow("cashbackInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << -0.02 << 0.2 << false;
    QTest::newRow("cashbackInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 1.02 << 0.2 << false;
    QTest::newRow("taxInvalid1_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << -0.2 << false;
    QTest::newRow("taxInvalid2_shouldFail") << validMaterial << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 1.2 << false;

    QTest::newRow("invalidMaterial_shouldFail") << invalidMaterial1 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
    QTest::newRow("nullMaterial_shouldFail") << invalidMaterial3 << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0.05 << 0.05 << 0.2 << 0.02 << 0.2 << false;
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
    QFETCH(double, materialOverhead);
    QFETCH(double, factoryOverhead);
    QFETCH(double, profit);
    QFETCH(double, cashback);
    QFETCH(double, tax);
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
    item->setMaterialCost(Decimal::fromValue(1.0));
    item->setPrice(Decimal::fromValue(5.0));
    item->setWorkingHours(10);
    item->setWagePerHour(Decimal::fromValue(1.3));
    item->setQuantity(5);
    item->setUnit("unit");
    item->setMaterialOverhead(0.05);
    item->setFactoryOverhead(0.05);
    item->setProfit(0.2);
    item->setCashback(0.02);
    item->setTaxRate(0.2);

    QMap<Material::Ptr, double> m;
    m.insert(material1, 1.2);
    m.insert(material2, 2.4);
    item->setMaterial(m);

    m_billItemDAO->create(item);
    QVERIFY(item->id() >= 0);

    // WHEN / THEN
    item->setDescription(desc);
    item->setMaterialCost(Decimal::fromValue(cost));
    item->setPrice(Decimal::fromValue(price));
    item->setWorkingHours(hours);
    item->setWagePerHour(Decimal::fromValue(wage));
    item->setQuantity(quantity);
    item->setUnit(unit);
    item->setMaterialOverhead(materialOverhead);
    item->setFactoryOverhead(factoryOverhead);
    item->setProfit(profit);
    item->setCashback(cashback);
    item->setTaxRate(tax);

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
    item->setMaterialCost(Decimal::fromValue(1.0));
    item->setPrice(Decimal::fromValue(5.0));
    item->setWorkingHours(10);
    item->setWagePerHour(Decimal::fromValue(1.3));
    item->setQuantity(5);
    item->setUnit("unit");
    item->setMaterialOverhead(0.05);
    item->setFactoryOverhead(0.05);
    item->setProfit(0.2);
    item->setCashback(0.02);
    item->setTaxRate(0.2);

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
    item->setMaterialCost(Decimal::fromValue(1.0));
    item->setPrice(Decimal::fromValue(5.0));
    item->setWorkingHours(10);
    item->setWagePerHour(Decimal::fromValue(1.3));
    item->setQuantity(5);
    item->setUnit("unit");
    item->setMaterialOverhead(0.05);
    item->setFactoryOverhead(0.05);
    item->setProfit(0.2);
    item->setCashback(0.02);
    item->setTaxRate(0.2);

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
    item->setMaterialCost(Decimal::fromValue(1.0));
    item->setPrice(Decimal::fromValue(5.0));
    item->setWorkingHours(10);
    item->setWagePerHour(Decimal::fromValue(1.3));
    item->setQuantity(5);
    item->setUnit("unit");
    item->setMaterialOverhead(0.05);
    item->setFactoryOverhead(0.05);
    item->setProfit(0.2);
    item->setCashback(0.02);
    item->setTaxRate(0.2);

    m_billItemDAO->create(item);
    QVERIFY(item->id() >= 0);

    QCOMPARE(m_billItemDAO->getAll().size(), prevDataSetCount + 1);
}

