#include "billitemdaotest.h"

void BillItemDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_customerDAO = std::make_shared<DBCustomerDAO>(testDB, std::make_shared<CustomerValidator>());
    m_billDAO = std::make_shared<DBBillDAO>(testDB, std::make_shared<BillValidator>(), m_customerDAO);
    m_billItemDAO = std::make_shared<DBBillItemDAO>(testDB, std::make_shared<BillItemValidator>(), m_billDAO);

    // create dummy customer
    Customer::Ptr customer = std::make_shared<Customer>();
    customer->setCity("city");
    customer->setStreet("street");
    customer->setMail("mail");
    customer->setName("name");
    customer->setSurname("surname");
    customer->setTitle("title");
    customer->setOrganisation("org");
    QVERIFY(m_customerDAO->create(customer));
    QVERIFY(customer->id() >= 0);

    // create dummy bill
    m_validBill = std::make_shared<Bill>();
    m_validBill->setBillNumber(1);
    m_validBill->setCustomer(customer);
    m_validBill->setPayed(false);
    m_validBill->setDate(QDate::currentDate());
    QVERIFY(m_billDAO->create(m_validBill));
    QVERIFY(m_validBill->id() >= 0);
}

void BillItemDAOTest::insertTest_data()
{
    QTest::addColumn<QString>("desc");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<double>("cost");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("hours");
    QTest::addColumn<double>("wage");
    QTest::addColumn<double>("quantity");
    QTest::addColumn<Bill::Ptr>("bill");
    QTest::addColumn<bool>("result");

    // create dummy invalid bills
    Bill::Ptr invalid_bill = std::make_shared<Bill>();
    Bill::Ptr no_bill = nullptr;

    // create test data

    QTest::newRow("validData_shouldPass") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << m_validBill << true;
    QTest::newRow("descEmpty_shouldFail") << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << m_validBill << false;
    QTest::newRow("UnitEmpty_shouldFail") << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << m_validBill << false;
    QTest::newRow("invalidBill_shouldFail") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << invalid_bill << false;
    QTest::newRow("NoBill_shouldFail") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << no_bill << false;
}

void BillItemDAOTest::insertTest()
{
    QFETCH(QString, desc);
    QFETCH(QString, unit);
    QFETCH(double, cost);;
    QFETCH(double, price);
    QFETCH(double, hours);
    QFETCH(double, wage);
    QFETCH(double, quantity);
    QFETCH(Bill::Ptr, bill);
    QFETCH(bool, result);

    BillItem::Ptr item = std::make_shared<BillItem>();
    item->setDescription(desc);
    item->setMaterialCost(cost);
    item->setPrice(price);
    item->setWorkingHours(hours);
    item->setWagePerHour(wage);
    item->setQuantity(quantity);
    item->setUnit(unit);
    item->setBill(bill);

    QCOMPARE(m_billItemDAO->create(item), result);

    if(result) {
        QVERIFY(item->id() >= 0);
        BillItem::Ptr itemFromData = m_billItemDAO->get(item->id());

        qDebug()<< "####";
        qDebug()<< item->toString();
        qDebug()<< itemFromData->toString();
        qDebug()<< "####";

        QVERIFY(item->equals(itemFromData));
    }
}

void BillItemDAOTest::updateTest_data()
{
    QTest::addColumn<QString>("desc");
    QTest::addColumn<QString>("unit");
    QTest::addColumn<double>("cost");
    QTest::addColumn<double>("price");
    QTest::addColumn<double>("hours");
    QTest::addColumn<double>("wage");
    QTest::addColumn<double>("quantity");
    QTest::addColumn<Bill::Ptr>("bill");
    QTest::addColumn<bool>("result");

    // create dummy invalid bills
    Bill::Ptr invalid_bill = std::make_shared<Bill>();
    Bill::Ptr no_bill = nullptr;

    QTest::newRow("validData_shouldPass") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << m_validBill << true;
    QTest::newRow("descEmpty_shouldFail") << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << m_validBill << false;
    QTest::newRow("UnitEmpty_shouldFail") << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << m_validBill << false;
    QTest::newRow("invalidBill_shouldFail") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << invalid_bill << false;
    QTest::newRow("NoBill_shouldFail") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << no_bill << false;
}

void BillItemDAOTest::updateTest()
{
    QFETCH(QString, desc);
    QFETCH(QString, unit);
    QFETCH(double, cost);;
    QFETCH(double, price);
    QFETCH(double, hours);
    QFETCH(double, wage);
    QFETCH(double, quantity);
    QFETCH(Bill::Ptr, bill);
    QFETCH(bool, result);

    // PREPARE

    BillItem::Ptr item = std::make_shared<BillItem>();
    item->setDescription("desc");
    item->setMaterialCost(1.0);
    item->setPrice(5.0);
    item->setWorkingHours(10);
    item->setWagePerHour(1.3);
    item->setQuantity(5);
    item->setUnit("unit");
    item->setBill(m_validBill);

    QVERIFY(m_billItemDAO->create(item));
    QVERIFY(item->id() >= 0);

    // WHEN / THEN
    item->setDescription(desc);
    item->setMaterialCost(cost);
    item->setPrice(price);
    item->setWorkingHours(hours);
    item->setWagePerHour(wage);
    item->setQuantity(quantity);
    item->setUnit(unit);
    item->setBill(bill);

    QCOMPARE(m_billItemDAO->update(item), result);

    if(result) {
        BillItem::Ptr itemFromData = m_billItemDAO->get(item->id());
        QVERIFY(item->equals(itemFromData));
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
    item->setBill(m_validBill);

    // get not used id
    int id = 0;
    while(m_billItemDAO->get(id) != nullptr) {
        id++;
    }
    item->setId(id);

    QCOMPARE(m_billItemDAO->update(item), false);
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
    item->setBill(m_validBill);

    QVERIFY(m_billItemDAO->create(item));
    QVERIFY(item->id() >= 0);

    int prevDataSetCount = m_billItemDAO->getAll().size();

    // WHEN / THEN
    QCOMPARE(m_billItemDAO->remove(item), true);
    QCOMPARE(m_billItemDAO->getAll().size(), prevDataSetCount - 1);
}

void BillItemDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    BillItem::Ptr item = std::make_shared<BillItem>();
    // get not used id
    int id = 0;
    while(m_billItemDAO->get(id) != nullptr) {
        id++;
    }
    item->setId(id);

    // WHEN / THEN
    QCOMPARE(m_billItemDAO->remove(item), false);
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
    item->setBill(m_validBill);

    QVERIFY(m_billItemDAO->create(item));
    QVERIFY(item->id() >= 0);

    QCOMPARE(m_billItemDAO->getAll().size(), prevDataSetCount + 1);
}

