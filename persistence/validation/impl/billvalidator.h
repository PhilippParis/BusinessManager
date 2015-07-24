#ifndef BILLVALIDATOR_H
#define BILLVALIDATOR_H

#include <memory>

#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/validation/impl/customervalidator.h"
#include "persistence/validation/impl/billitemvalidator.h"
#include "domain/bill.h"

class BillValidator : public Validator<Bill::Ptr>
{
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
};

#endif // BILLVALIDATOR_H
