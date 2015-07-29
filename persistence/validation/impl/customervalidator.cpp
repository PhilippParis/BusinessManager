#include "customervalidator.h"

CustomerValidator::CustomerValidator()
{

}

void CustomerValidator::validateForCreate(Customer::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("customer must not be null");
    }

    validateMandatoryFields(item);
}

void CustomerValidator::validateForUpdate(Customer::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("customer must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void CustomerValidator::validateIdentity(Customer::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("customer must not be null");
    }

    if (item->id() < 0) {
        throw new ValidationException("customer must have a valid id");
    }
}

void CustomerValidator::validateMandatoryFields(Customer::Ptr item)
{
    if (item->city().isEmpty()) {
        throw new ValidationException(tr("city must not be emtpy"));
    }
    if (item->name().isEmpty()) {
        throw new ValidationException(tr("name must not be emtpy"));
    }
    if (item->surname().isEmpty()) {
        throw new ValidationException(tr("surname must not be emtpy"));
    }
    if (item->street().isEmpty()) {
        throw new ValidationException(tr("street must not be empty"));
    }
}

