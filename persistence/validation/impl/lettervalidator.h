#ifndef LETTERVALIDATOR_H
#define LETTERVALIDATOR_H

#include <QCoreApplication>
#include <QObject>
#include <memory>

#include "domain/letter.h"
#include "persistence/validation/validator.h"
#include "persistence/validation/impl/customervalidator.h"

class LetterValidator : public Validator<Letter::Ptr>
{
    Q_DECLARE_TR_FUNCTIONS(LetterValidator)
public:
    LetterValidator();

    void validateForCreate(Letter::Ptr item) override;
    void validateForUpdate(Letter::Ptr item) override;
    void validateIdentity(Letter::Ptr item) override;

private:
    void validateMandatoryFields(Letter::Ptr item);

private:
    Validator<Customer::Ptr>::Ptr m_customerValidator;
};

#endif // LETTERVALIDATOR_H
