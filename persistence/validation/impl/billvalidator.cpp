#include "billvalidator.h"

BillValidator::BillValidator()
{
    m_customerValidator = std::make_shared<CustomerValidator>();
    m_billItemValidator = std::make_shared<BillItemValidator>();
    m_discountValidator = std::make_shared<DiscountValidator>();
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
        throw new ValidationException(tr("bill number must not be negative"));
    }

    for(BillItem::Ptr billItem : item->items()) {
        // validate for create -> id of billitem must not be set
        m_billItemValidator->validateForCreate(billItem);
    }

    for(Discount::Ptr discount : item->discounts()) {
        // validate for create -> id of discount must not be set
        m_discountValidator->validateForCreate(discount);
    }

    m_customerValidator->validateIdentity(item->customer());
}

