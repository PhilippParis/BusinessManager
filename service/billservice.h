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

    /**
     * adds the bill to the underlying datasource
     * @param bill bill to add
     */
    virtual void addBill(Bill::Ptr bill) = 0;

    /**
     * updates the bill in the underlying datsource
     * adds billitems which id is not set;
     * updates billitems which have a valid id
     * @param bill bill to update
     */
    virtual void updateBill(Bill::Ptr bill) = 0;

    /**
     * removes bill from the underlying datasource
     * @param bill bill to remove
     */
    virtual void removeBill(Bill::Ptr bill) = 0;

    /**
     * @param id id of the bill
     * @return returns the bill with the specified id
     */
    virtual Bill::Ptr getBill(int id) = 0;

    /**
     * @return all bills from the underlying datsource
     */
    virtual QList<Bill::Ptr> getAllBills() = 0;

    /**
     * @param date billdate
     * @return returns the billnumber for the next bill
     */
    virtual int nextBillNumber(QDate date) = 0;

    /**
     * @return returns the date of the first and last bill
     */
    virtual QPair<QDate, QDate> billDateRange() = 0;

    /**
     * @return returns the billitem validator
     */
    virtual Validator<BillItem::Ptr>::Ptr billItemValidator() = 0;

    /**
     * @return returns the bill validator
     */
    virtual Validator<Bill::Ptr>::Ptr billValidator() = 0;

};

#endif // BILLSERVICE_H
