#ifndef DBBILLITEMDAO_H
#define DBBILLITEMDAO_H

#include "persistence/billitemdao.h"

class DBBillItemDAO : public BillItemDAO
{
public:
    DBBillItemDAO();
    ~DBBillItemDAO();
};

#endif // DBBILLITEMDAO_H
