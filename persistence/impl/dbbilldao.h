#ifndef DBBILLDAO_H
#define DBBILLDAO_H

#include <QSqlDatabase>

#include "persistence/validation/validator.h"
#include "persistence/billdao.h"

#include "domain/bill.h"

class DBBillDAO : public BillDAO
{
public:
    DBBillDAO(QSqlDatabase database, Validator<Bill::Ptr>::Ptr validator);
    ~DBBillDAO();
};

#endif // DBBILLDAO_H
