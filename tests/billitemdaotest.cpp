#include "billitemdaotest.h"

void BillItemDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_billItemDAO = new DBBillItemDAO(testDB, std::make_shared<BillItemValidator>());
    m_billDAO = new DBBillDAO(testDB, std::make_shared<BillValidator>());
    m_customerDAO = new DBCustomerDAO(testDB, std::make_shared<CustomerValidator>());
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

    // create dummy bill
    Bill::Ptr valid_bill = std::make_shared<Bill>();
    valid_bill->setBillNumber(1);
    valid_bill->setCustomer(customer);
    valid_bill->setPayed(false);
    QVERIFY(m_billDAO->create(valid_bill));

    // create dummy invalid bills
    Bill::Ptr invalid_bill = std::make_shared<Bill>();
    Bill::Ptr no_bill = nullptr;

    // create test data

    QTest::newRow("valid") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << valid_bill << true;
    QTest::newRow("no_desc") << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << valid_bill << false;
    QTest::newRow("no_unit") << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << valid_bill << false;
    QTest::newRow("invalid_bill") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << invalid_bill << false;
    QTest::newRow("no_bill") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << no_bill << false;
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
}

void BillItemDAOTest::updateTest()
{

}

void BillItemDAOTest::removeTest()
{

}

void BillItemDAOTest::getTest()
{

}
