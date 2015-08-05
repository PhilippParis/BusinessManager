#include "templatedaotest.h"

void TemplateDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_materialDAO = std::make_shared<DBMaterialDAO>(testDB, std::make_shared<MaterialValidator>());
    m_templateDAO = std::make_shared<DBTemplateDAO>(testDB, std::make_shared<TemplateValidator>(), m_materialDAO);

    // create dummy materials
    m_invalidMaterial = std::make_shared<Material>();
    m_nullMaterial = nullptr;

    m_validMaterial = std::make_shared<Material>();
    m_validMaterial->setName("material");
    m_validMaterial->setUnit("unit");

    m_materialDAO->create(m_validMaterial);
    QVERIFY(m_validMaterial->id() >= 0);
}

void TemplateDAOTest::insertTest_data()
{
    QTest::addColumn<QMap<Material::Ptr, double>>("material");
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
    QMap<Material::Ptr, double> validMaterial;
    validMaterial.insert(m_validMaterial, 2.0);

    QMap<Material::Ptr, double> invalidMaterial1;
    invalidMaterial1.insert(m_invalidMaterial, 2.0);

    QMap<Material::Ptr, double> invalidMaterial2;
    invalidMaterial2.insert(m_validMaterial, -2.0);

    QMap<Material::Ptr, double> invalidMaterial3;
    invalidMaterial3.insert(m_nullMaterial, 2.0);

    // create test data

    QTest::newRow("validData_shouldPass") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << true;
    QTest::newRow("itemDescEmpty_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << ""<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "" << 10.0 << 500.0 << false;
    QTest::newRow("negativePrice_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << -500.0 << false;
    QTest::newRow("negativeHourse_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << -10.0 << 500.0 << false;

    QTest::newRow("invalidMaterial_shouldFail") << invalidMaterial1 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("nullMaterial_shouldFail") << invalidMaterial3 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
}

void TemplateDAOTest::insertTest()
{
    typedef QMap<Material::Ptr, double> MaterialMap;

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
    templ->setPrice(Decimal::fromValue(price));
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
    QTest::addColumn<QMap<Material::Ptr, double>>("material");
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
    QMap<Material::Ptr, double> validMaterial;
    validMaterial.insert(m_validMaterial, 2.0);

    QMap<Material::Ptr, double> invalidMaterial1;
    invalidMaterial1.insert(m_invalidMaterial, 2.0);

    QMap<Material::Ptr, double> invalidMaterial2;
    invalidMaterial2.insert(m_validMaterial, -2.0);

    QMap<Material::Ptr, double> invalidMaterial3;
    invalidMaterial3.insert(m_nullMaterial, 2.0);

    // create test data

    QTest::newRow("validData_shouldPass") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << true;
    QTest::newRow("itemDescEmpty_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << ""<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("UnitEmpty_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "" << 10.0 << 500.0 << false;
    QTest::newRow("negativePrice_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << -500.0 << false;
    QTest::newRow("negativeHourse_shouldFail") << validMaterial << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << -10.0 << 500.0 << false;

    QTest::newRow("invalidMaterial_shouldFail") << invalidMaterial1 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("negativeQuantity_shouldFail") << invalidMaterial2 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
    QTest::newRow("nullMaterial_shouldFail") << invalidMaterial3 << "name" << "org" << "type" << "desc" << "itemDesc"<< "m" << 10.0 << 500.0 << false;
}

void TemplateDAOTest::updateTest()
{
    typedef QMap<Material::Ptr, double> MaterialMap;

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
    // create materials
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

    // create valid template
    Template::Ptr templ = std::make_shared<Template>();
    templ->setName("desc");
    templ->setOrganisation("org");
    templ->setType("type");
    templ->setDesc("desc");
    templ->setItemDesc("itemDesc");
    templ->setUnit("unit");
    templ->setWorkingHours(1.0);
    templ->setPrice(Decimal::fromValue(10.0));

    QMap<Material::Ptr, double> m;
    m.insert(material1, 1.2);
    m.insert(material2, 2.4);
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
    templ->setPrice(Decimal::fromValue(price));
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
    templ->setPrice(Decimal::fromValue(10.0));

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
    templ->setPrice(Decimal::fromValue(10.0));

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
    templ->setPrice(Decimal::fromValue(10.0));

    m_templateDAO->create(templ);
    QVERIFY(templ->id() >= 0);

    QCOMPARE(m_templateDAO->getAll().size(), prevDataSetCount + 1);
}
