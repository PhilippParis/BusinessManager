#ifndef BILLVALIDATOR_H
#define BILLVALIDATOR_H

#include <QCoreApplication>
#include <memory>

#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/validation/impl/customervalidator.h"
#include "persistence/validation/impl/billitemvalidator.h"
#include "persistence/validation/impl/discountvalidator.h"
#include "domain/bill.h"

class BillValidator : public Validator<Bill::Ptr>
{
    Q_DECLARE_TR_FUNCTIONS(BillValidator)
public:
    BillValidator();

    void validateForCreate(Bill::Ptr item) override;
    void validateForUpdate(Bill::Ptr item) override;
    void validateIdentity(Bill::Ptr item) override;

private:
    void validateMandatoryFields(Bill::Ptr item);

private:
    Validator<Customer::Ptr>::Ptr m_customerValidator;
    Validator<BillItem::Ptr>::Ptr m_billItemValidator;
    Validator<Discount::Ptr>::Ptr m_discountValidator;
};

#endif // BILLVALIDATOR_H
