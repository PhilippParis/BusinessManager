#ifndef BILLSERVICEIMPL_H
#define BILLSERVICEIMPL_H

#include "service/billservice.h"

#include "persistence/billdao.h"
#include "persistence/billitemdao.h"
#include "persistence/discountdao.h"
#include "persistence/validation/validator.h"

class BillServiceImpl : public BillService
{
public:
    BillServiceImpl(BillDAO::Ptr billDAO, BillItemDAO::Ptr billItemDAO, DiscountDAO::Ptr discountDAO,
                    Validator<Bill::Ptr>::Ptr billValidator, Validator<BillItem::Ptr>::Ptr billItemValidator);

    void addBill(Bill::Ptr bill) override;
    void updateBill(Bill::Ptr bill) override;
    void removeBill(Bill::Ptr bill) override;
    Bill::Ptr getBill(int id) override;
    QList<Bill::Ptr> getAllBills() override;

    int nextBillNumber(QDate date) override;
    QPair<QDate, QDate> billDateRange() override;

    Validator<BillItem::Ptr>::Ptr billItemValidator();
    Validator<Bill::Ptr>::Ptr billValidator();

private:
    void addItem(BillItem::Ptr item);
    void updateItem(BillItem::Ptr item);
    void removeItem(BillItem::Ptr item);

private:
    BillDAO::Ptr m_billDAO;
    BillItemDAO::Ptr m_billItemDAO;
    DiscountDAO::Ptr m_discountDAO;

    Validator<Bill::Ptr>::Ptr m_billValidator;
    Validator<BillItem::Ptr>::Ptr m_billItemValidator;

};

#endif // BILLSERVICEIMPL_H
