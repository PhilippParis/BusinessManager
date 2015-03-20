#ifndef DBBILLDAO_H
#define DBBILLDAO_H

#include "persistence/billdao.h"

class DBBillDAO : public BillDAO
{
public:
    DBBillDAO();
    ~DBBillDAO();
};

#endif // DBBILLDAO_H
