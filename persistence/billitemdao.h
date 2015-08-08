#ifndef BILLITEMDAO_H
#define BILLITEMDAO_H

#include "domain/billitem.h"
#include "persistence/persistenceexception.h"
#include "persistence/validation/validator.h"

#include "persistence/itemdao.h"

class BillItemDAO : public ItemDAO
{
public:
    typedef std::shared_ptr<BillItemDAO> Ptr;

    BillItemDAO();
    ~BillItemDAO();

    /**
     * @param billID id of the bill
     * @return returns all items of a bill
     */
    virtual QList<BillItem::Ptr> getItemsOfBill(int billID) = 0;
};

#endif // BILLITEMDAO_H
