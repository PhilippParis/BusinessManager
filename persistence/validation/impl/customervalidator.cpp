#include "customervalidator.h"

CustomerValidator::CustomerValidator()
{

}

bool CustomerValidator::validateForCreate(Customer::Ptr item)
{
    return item != nullptr && validateMandatoryFields(item);
}

bool CustomerValidator::validateForUpdate(Customer::Ptr item)
{
    return item != nullptr && validateMandatoryFields(item) && validateIdentity(item);
}

bool CustomerValidator::validateIdentity(Customer::Ptr item)
{
    return item != nullptr && item->id() >= 0;
}

bool CustomerValidator::validateMandatoryFields(Customer::Ptr item)
{
    if (item->city().isEmpty()) {
        qCDebug(lcValidation()) << "city must not be emtpy";
        return false;
    }
    if (item->name().isEmpty()) {
        qCDebug(lcValidation()) << "name must not be empty";
        return false;
    }
    if (item->surname().isEmpty()) {
        qCDebug(lcValidation()) << "surname must not be empty";
        return false;
    }
    if (item->street().isEmpty()) {
        qCDebug(lcValidation()) << "street must not be empty";
        return false;
    }
    return true;
}

