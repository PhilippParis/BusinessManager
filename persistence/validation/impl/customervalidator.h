#ifndef CUSTOMERVALIDATOR_H
#define CUSTOMERVALIDATOR_H

#include <memory>

#include "logging.h"

#include "domain/customer.h"
#include "persistence/validation/validator.h"

class CustomerValidator : public Validator<Customer::Ptr>
{
public:
    CustomerValidator();

    bool validateForCreate(Customer::Ptr item) override;
    bool validateForUpdate(Customer::Ptr item) override;
    bool validateIdentity(Customer::Ptr item) override;

private:
    bool validateMandatoryFields(Customer::Ptr item);
};

#endif // CUSTOMERVALIDATOR_H
