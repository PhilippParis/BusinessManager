#include "billitemdaotest.h"

void BillItemDAOTest::initTestCase()
{
    m_dao = new DBBillItemDAO(DatabaseSingleton::get()->getTestDatabase(), std::make_shared<BillItemValidator>());
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
    QTest::addColumn<int>("billID");
    QTest::addColumn<bool>("result");

    QTest::newRow("valid") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0 << true;
    QTest::newRow("no_desc") << "" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0 << false;
    QTest::newRow("no_unit") << "desc1" << "" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << 0 << false;
    QTest::newRow("invalid_bill") << "desc1" << "m" << 100.0 << 500.0 << 10.0 << 9.99 << 10.0 << -2 << false;
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
    QFETCH(int, billID);
    QFETCH(bool, result);

    BillItem::Ptr item = std::make_shared<BillItem>();

    item->setDescription(desc);
    item->setMaterialCost(cost);
    item->setPrice(price);
    item->setWorkingHours(hours);
    item->setWagePerHour(wage);
    item->setQuantity(quantity);
    item->setUnit(unit);

    QCOMPARE(m_dao->write(item, billID), result);
    QCOMPARE(compareWithDatabase(item, billID), result);
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
