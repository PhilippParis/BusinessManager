#include "discountvalidator.h"

DiscountValidator::DiscountValidator()
{

}

void DiscountValidator::validateForCreate(Discount::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("discount must not be null");
    }

    validateMandatoryFields(item);
}

void DiscountValidator::validateForUpdate(Discount::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("discount must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void DiscountValidator::validateIdentity(Discount::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("discount must not be null");
    }
    if (item->id() < 0) {
        throw new ValidationException("discount must have a valid id");
    }
}

void DiscountValidator::validateMandatoryFields(Discount::Ptr item)
{
    if(item->value() < Decimal::fromValue(0.0)) {
        throw new ValidationException(tr("discount must not be negative"));
    }
}

