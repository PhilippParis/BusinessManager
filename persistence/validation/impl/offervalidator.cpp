#include "offervalidator.h"

OfferValidator::OfferValidator()
{
    m_customerValidator = std::make_shared<CustomerValidator>();
    m_billItemValidator = std::make_shared<BillItemValidator>();
}

void OfferValidator::validateForCreate(Offer::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("offer must not be null");
    }

    validateMandatoryFields(item);
}

void OfferValidator::validateForUpdate(Offer::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("offer must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void OfferValidator::validateIdentity(Offer::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("offer must not be null");
    }

    if (item->id() < 0) {
        throw new ValidationException("offer must have a valid id");
    }
}

void OfferValidator::validateMandatoryFields(Offer::Ptr item)
{
    if (!item->date().isValid()) {
        throw new ValidationException(tr("date must be valid"));
    }

    for(BillItem::Ptr billItem : item->items()) {
        // validate for create -> id of Offeritem must not be set
        m_billItemValidator->validateForCreate(billItem);
    }

    m_customerValidator->validateIdentity(item->customer());
}
