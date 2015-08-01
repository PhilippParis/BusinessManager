#ifndef BILLSERVICE_H
#define BILLSERVICE_H

#include <memory>

#include "domain/bill.h"
#include "domain/billitem.h"

#include "service/serviceexception.h"
#include "persistence/validation/validator.h"

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

    virtual int nextBillNumber(QDate date) = 0;
    virtual QPair<QDate, QDate> billDateRange() = 0;

    virtual Validator<BillItem::Ptr>::Ptr billItemValidator() = 0;
    virtual Validator<Bill::Ptr>::Ptr billValidator() = 0;

};

#endif // BILLSERVICE_H
