#ifndef DBPRODUCTDAO_H
#define DBPRODUCTDAO_H

#include "persistence/productdao.h"

class DBProductDAO : public ProductDAO
{
public:
    DBProductDAO();
    ~DBProductDAO();
};

#endif // DBPRODUCTDAO_H
