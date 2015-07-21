#ifndef BILLSERVICE_H
#define BILLSERVICE_H

#include <memory>

#include "domain/bill.h"
#include "domain/billitem.h"

#include "service/serviceexception.h"

class BillService
{
public:
    typedef std::shared_ptr<BillService> Ptr;

    BillService();

    virtual void addBill(Bill::Ptr bill) = 0;
    virtual void updateBill(Bill::Ptr bill) = 0;
    virtual void removeBill(Bill::Ptr bill) = 0;
    virtual Bill::Ptr getBill(int id) = 0;
    virtual QList<Bill::Ptr> getAllBills() = 0;

    virtual void addItem(BillItem::Ptr item) = 0;
    virtual void updateItem(BillItem::Ptr item) = 0;
    virtual void removeItem(BillItem::Ptr item) = 0;
    virtual BillItem::Ptr getItem(int id) = 0;
    virtual QList<BillItem::Ptr> getItemsOfBill(int billID) = 0;

};

#endif // BILLSERVICE_H
