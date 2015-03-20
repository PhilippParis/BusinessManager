#ifndef DBCUSTOMERDAO_H
#define DBCUSTOMERDAO_H

#include "persistence/customerdao.h"

class DBCustomerDAO : public CustomerDAO
{
public:
    DBCustomerDAO();
    ~DBCustomerDAO();
};

#endif // DBCUSTOMERDAO_H
