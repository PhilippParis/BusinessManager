#ifndef BILLSERVICEIMPL_H
#define BILLSERVICEIMPL_H

#include "service/billservice.h"

#include "persistence/billdao.h"
#include "persistence/billitemdao.h"
#include "persistence/validation/validator.h"

class BillServiceImpl : public BillService
{
public:
    BillServiceImpl(BillDAO::Ptr billDAO, BillItemDAO::Ptr billItemDAO,
                    Validator<Bill::Ptr>::Ptr billValidator, Validator<BillItem::Ptr>::Ptr billItemValidator);

    void addBill(Bill::Ptr bill) override;
    void updateBill(Bill::Ptr bill) override;
    void removeBill(Bill::Ptr bill) override;
    Bill::Ptr getBill(int id) override;
    QList<Bill::Ptr> getAllBills() override;

    void addItem(BillItem::Ptr item) override;
    void updateItem(BillItem::Ptr item) override;
    void removeItem(BillItem::Ptr item) override;
    BillItem::Ptr getItem(int id) override;
    QList<BillItem::Ptr> getItemsOfBill(int billID) override;


private:
    BillDAO::Ptr m_billDAO;
    BillItemDAO::Ptr m_billItemDAO;
    Validator<Bill::Ptr>::Ptr m_billValidator;
    Validator<BillItem::Ptr>::Ptr m_billItemValidator;

};

#endif // BILLSERVICEIMPL_H
