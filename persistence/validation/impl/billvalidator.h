#ifndef BILLVALIDATOR_H
#define BILLVALIDATOR_H

#include <memory>

#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/validation/impl/customervalidator.h"
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
};

#endif // BILLVALIDATOR_H
