#include "dbbilldao.h"

DBBillDAO::DBBillDAO(QSqlDatabase database, Validator<Bill::Ptr>::Ptr validator)
 : m_database(database),
   m_validator(validator)
{

}

Bill::Ptr DBBillDAO::get(int id)
{

}

QList<Bill::Ptr> DBBillDAO::getAll()
{

}

bool DBBillDAO::create(Bill::Ptr item)
{

}

bool DBBillDAO::update(Bill::Ptr item)
{

}

bool DBBillDAO::remove(Bill::Ptr item)
{

}

Bill::Ptr DBBillDAO::parseBill(QSqlRecord record)
{

}


