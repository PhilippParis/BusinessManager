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

    bool validateForCreate(Bill::Ptr item) override;
    bool validateForUpdate(Bill::Ptr item) override;
    bool validateIdentity(Bill::Ptr item) override;

private:
    bool validateMandatoryFields(Bill::Ptr item);

private:
    Validator<Customer::Ptr>::Ptr m_customerValidator;
};

#endif // BILLVALIDATOR_H
