#include "productvalidator.h"

ProductValidator::ProductValidator()
{

}

void ProductValidator::validateForCreate(Product::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("customer must not be null");
    }

    validateMandatoryFields(item);
}

void ProductValidator::validateForUpdate(Product::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("customer must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void ProductValidator::validateIdentity(Product::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("customer must not be null");
    }

    if (item->id() < 0) {
        throw new ValidationException("customer must have a valid id");
    }
}

void ProductValidator::validateMandatoryFields(Product::Ptr item)
{
    if (item->name().isEmpty()) {
        throw new ValidationException("name must not be empty");
    }
    if (item->costPerUnit() < 0) {
        throw new ValidationException("cost must not be negative");
    }
    if (item->pricePerUnit() < 0) {
        throw new ValidationException("price must not be negative");
    }
    if (item->unit().isEmpty()) {
        throw new ValidationException("unit must not be empty");
    }
}
