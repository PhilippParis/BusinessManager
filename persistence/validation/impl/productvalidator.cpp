#include "productvalidator.h"

ProductValidator::ProductValidator()
{

}

bool ProductValidator::validateForCreate(Product::Ptr item)
{
    return item != nullptr && validateMandatoryFields(item);
}

bool ProductValidator::validateForUpdate(Product::Ptr item)
{
    return item != nullptr && validateMandatoryFields(item) && validateIdentity(item);
}

bool ProductValidator::validateIdentity(Product::Ptr item)
{
    return item != nullptr && item->id() >= 0;
}

bool ProductValidator::validateMandatoryFields(Product::Ptr item)
{
    if (item->name().isEmpty()) {
        qCDebug(lcValidation()) << "name must not be emtpy";
        return false;
    }
    if (item->costPerUnit() < 0) {
        qCDebug(lcValidation()) << "cost must not be negative";
        return false;
    }
    if (item->pricePerUnit() < 0) {
        qCDebug(lcValidation()) << "price must not be negative";
        return false;
    }
    if (item->unit().isEmpty()) {
        qCDebug(lcValidation()) << "unit must not be empty";
        return false;
    }
    return true;
}
