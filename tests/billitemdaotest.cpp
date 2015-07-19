#include "billitemdaotest.h"

void BillItemDAOTest::initTestCase()
{
    m_billItemDao = new DBBillItemDAO(DatabaseSingleton::get()->getTestDatabase(), std::make_shared<BillItemValidator>());
    m_billDao = new DBBillDAO(DatabaseSingleton::get()->getTestDatabase(), std::make_shared<BillValidator>());
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

    Bill::Ptr valid_bill = std::make_shared<Bill>();


    Bill::Ptr invalid_bill = std::make_shared<Bill>();
    Bill::Ptr no_bill = nullptr;

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

    QCOMPARE(m_billItemDao->write(item), result);
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

bool BillItemDAOTest::compareWithDatabase(BillItem::Ptr item, int billID)
{
    return false;
}
