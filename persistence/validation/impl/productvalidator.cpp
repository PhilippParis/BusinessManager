#include "productvalidator.h"

ProductValidator::ProductValidator()
{

}

void ProductValidator::validateForCreate(Product::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("product must not be null");
    }

    validateMandatoryFields(item);
}

void ProductValidator::validateForUpdate(Product::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("product must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void ProductValidator::validateIdentity(Product::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("product must not be null");
    }

    if (item->id() < 0) {
        throw new ValidationException("product must have a valid id");
    }
}

void ProductValidator::validateMandatoryFields(Product::Ptr item)
{
    if (item->name().isEmpty()) {
        throw new ValidationException(tr("name must not be empty"));
    }
    if (item->costPerUnit() < 0) {
        throw new ValidationException(tr("cost must not be negative"));
    }
    if (item->tax() < 0) {
        throw new ValidationException(tr("tax must not be negative"));
    }
    if (item->unit().isEmpty()) {
        throw new ValidationException(tr("unit must not be empty"));
    }
}
