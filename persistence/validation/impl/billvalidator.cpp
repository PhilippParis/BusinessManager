#include "billvalidator.h"

BillValidator::BillValidator()
{
    m_customerValidator = std::make_shared<CustomerValidator>();
}

void BillValidator::validateForCreate(Bill::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("bill must not be null");
    }

    validateMandatoryFields(item);
}

void BillValidator::validateForUpdate(Bill::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("bill must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void BillValidator::validateIdentity(Bill::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("bill must not be null");
    }

    if (item->id() < 0) {
        throw new ValidationException("bill must have a valid id");
    }
}

void BillValidator::validateMandatoryFields(Bill::Ptr item)
{
    if (item->billNumber() <= 0) {
        throw new ValidationException("bill number must not be negative");
    }

    m_customerValidator->validateIdentity(item->customer());
}

