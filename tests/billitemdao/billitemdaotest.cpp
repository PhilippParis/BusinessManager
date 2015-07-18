#include "billitemdaotest.h"
void BillItemDAOTest::initTestCase()
{
    QSqlDatabase db =  QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("dataBase.db");
    if(!db.open()) {
        qDebug()<<"FAILED TO OPEN";
        return;
    }
    m_dao = new DBBillItemDAO(db);
}

void BillItemDAOTest::insertTest()
{
    BillItem::Ptr item = std::make_shared<BillItem>();

    item->setDescription("desc");
    item->setMaterialCost(100.0);
    item->setPrice(500.0);
    item->setWorkingHours(40.0);
    item->setWagePerHour(10.0);
    item->setQuantity(5.0);
    item->setUnit("unit");

    m_dao->write(item, 0);
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
DECLARE_TEST(BillItemDAOTest)
