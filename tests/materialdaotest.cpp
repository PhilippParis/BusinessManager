#include "materialdaotest.h"

void MaterialDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_materialDAO = std::make_shared<DBMaterialDAO>(testDB, std::make_shared<MaterialValidator>());
}

void MaterialDAOTest::insertTest_data()
{
    QTest::addColumn<QString>("nr");
    QTest::addColumn<double>("cost");
    QTest::addColumn<double>("tax");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<QString>("desc");
    QTest::addColumn<bool>("result");

    QTest::newRow("validData_shouldPass") << "Z1" << 1.0 << 2.0 << "name" << "type" << "unit" << "desc" << true;
    QTest::newRow("negativeCost_shouldFail") << "1" << -1.0 << 2.0 << "name" << "type" << "unit" << "desc" << false;
    QTest::newRow("negativetax_shouldFail") << "1" << 1.0 << -2.0 << "name" << "type" << "unit" << "desc" << false;
    QTest::newRow("emptyName_shouldFail") << "1" << 1.0 << 2.0 << "" << "type" << "unit" << "desc" << false;
    QTest::newRow("emptyUnit_shouldFail") << "1" << 1.0 << 2.0 << "name" << "type" << "" << "desc" << false;
}

void MaterialDAOTest::insertTest()
{
    QFETCH(QString, nr);
    QFETCH(double, cost);
    QFETCH(double, tax);
    QFETCH(QString, name);
    QFETCH(QString, type);
    QFETCH(QString, unit);
    QFETCH(QString, desc);
    QFETCH(bool, result);

    Material::Ptr material = std::make_shared<Material>();
    material->setName(name);
    material->setCostPerUnit(cost);
    material->setTax(tax);
    material->setName(name);
    material->setType(type);
    material->setUnit(unit);
    material->setManufactor(desc);
    material->setArticleNumber(nr);

    try {
        m_materialDAO->create(material);
        QVERIFY(material->id() >= 0);

        Material::Ptr materialFromData = m_materialDAO->get(material->id());
        QVERIFY(material->equals(materialFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void MaterialDAOTest::updateTest_data()
{
    QTest::addColumn<QString>("nr");
    QTest::addColumn<double>("cost");
    QTest::addColumn<double>("tax");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("type");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<QString>("desc");
    QTest::addColumn<bool>("result");

    QTest::newRow("validData_shouldPass") << "Z1" << 1.0 << 2.0 << "name" << "type" << "unit" << "desc" << true;
    QTest::newRow("negativeCost_shouldFail") << "1" << -1.0 << 2.0 << "name" << "type" << "unit" << "desc" << false;
    QTest::newRow("negativetax_shouldFail") << "1" << 1.0 << -2.0 << "name" << "type" << "unit" << "desc" << false;
    QTest::newRow("emptyName_shouldFail") << "1" << 1.0 << 2.0 << "" << "type" << "unit" << "desc" << false;
    QTest::newRow("emptyUnit_shouldFail") << "1" << 1.0 << 2.0 << "name" << "type" << "" << "desc" << false;
}

void MaterialDAOTest::updateTest()
{
    QFETCH(QString, nr);
    QFETCH(double, cost);
    QFETCH(double, tax);
    QFETCH(QString, name);
    QFETCH(QString, type);
    QFETCH(QString, unit);
    QFETCH(QString, desc);
    QFETCH(bool, result);

    Material::Ptr material = std::make_shared<Material>();
    material->setName("name");
    material->setCostPerUnit(1.0);
    material->setTax(2.0);
    material->setName("name");
    material->setType("type");
    material->setUnit("unit");
    material->setManufactor("desc");
    material->setArticleNumber(nr);

    m_materialDAO->create(material);
    QVERIFY(material->id() >= 0);
    Material::Ptr materialFromData = m_materialDAO->get(material->id());
    QVERIFY(material->equals(materialFromData));

    material->setName(name);
    material->setCostPerUnit(cost);
    material->setTax(tax);
    material->setName(name);
    material->setType(type);
    material->setUnit(unit);
    material->setManufactor(desc);

    try {
        m_materialDAO->update(material);
        materialFromData = m_materialDAO->get(material->id());
        QVERIFY(material->equals(materialFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void MaterialDAOTest::updateWithInvalidIDTest()
{
    // PREPARE
    Material::Ptr material = std::make_shared<Material>();
    material->setName("name");
    material->setCostPerUnit(1.0);
    material->setTax(2.0);
    material->setName("name");
    material->setType("type");
    material->setUnit("unit");
    material->setManufactor("desc");

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_materialDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    material->setId(id);

    try {
        m_materialDAO->update(material);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void MaterialDAOTest::removeTestWithValidIDShouldPass()
{
    // PREPARE
    Material::Ptr material = std::make_shared<Material>();
    material->setName("name");
    material->setCostPerUnit(1.0);
    material->setTax(2.0);
    material->setName("name");
    material->setType("type");
    material->setUnit("unit");
    material->setManufactor("desc");

    m_materialDAO->create(material);
    QVERIFY(material->id() >= 0);

    int prevDataSetCount = m_materialDAO->getAll().size();

    // WHEN / THEN
    m_materialDAO->remove(material);
    QCOMPARE(m_materialDAO->getAll().size(), prevDataSetCount - 1);
}

void MaterialDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    Material::Ptr material = std::make_shared<Material>();

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_materialDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    material->setId(id);

    // WHEN / THEN
    try {
        m_materialDAO->remove(material);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void MaterialDAOTest::getAllTest()
{
    int prevDataSetCount = m_materialDAO->getAll().size();

    // PREPARE
    Material::Ptr material = std::make_shared<Material>();
    material->setName("name");
    material->setCostPerUnit(1.0);
    material->setTax(2.0);
    material->setName("name");
    material->setType("type");
    material->setUnit("unit");
    material->setManufactor("desc");

    // WHEN / THEN
    m_materialDAO->create(material);
    QVERIFY(material->id() >= 0);

    QCOMPARE(m_materialDAO->getAll().size(), prevDataSetCount + 1);
}
