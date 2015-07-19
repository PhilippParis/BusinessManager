#include "billvalidator.h"

BillValidator::BillValidator()
{
    m_customerValidator = std::make_shared<CustomerValidator>();
}

bool BillValidator::validateForCreate(Bill::Ptr item)
{
    return item != nullptr && validateMandatoryFields(item);
}

bool BillValidator::validateForUpdate(Bill::Ptr item)
{
    return item != nullptr && validateMandatoryFields(item) && validateIdentity(item);
}

bool BillValidator::validateIdentity(Bill::Ptr item)
{
    return item != nullptr && item->id() >= 0;
}

bool BillValidator::validateMandatoryFields(Bill::Ptr item)
{
    if (item->billNumber() <= 0) {
        qCDebug(lcValidation) << "bill number must be > 0";
        return false;
    }

    if (!m_customerValidator->validateIdentity(item->customer())) {
        qCDebug(lcValidation()) << "customer must have a valid id";
        return false;
    }
    return true;
}

