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

    void validateForCreate(Customer::Ptr item) override;
    void validateForUpdate(Customer::Ptr item) override;
    void validateIdentity(Customer::Ptr item) override;

private:
    void validateMandatoryFields(Customer::Ptr item);
};

#endif // CUSTOMERVALIDATOR_H
