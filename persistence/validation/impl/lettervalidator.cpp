#include "lettervalidator.h"

LetterValidator::LetterValidator()
{
    m_customerValidator = std::make_shared<CustomerValidator>();
}

void LetterValidator::validateForCreate(Letter::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("letter must not be null");
    }

    validateMandatoryFields(item);
}

void LetterValidator::validateForUpdate(Letter::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("letter must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void LetterValidator::validateIdentity(Letter::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("letter must not be null");
    }
    if (item->id() < 0) {
        throw new ValidationException("letter must have a valid id");
    }
}

void LetterValidator::validateMandatoryFields(Letter::Ptr item)
{
    if(!item->date().isValid()) {
        throw new ValidationException(tr("date must be valid"));
    }

    m_customerValidator->validateIdentity(item->customer());
}
