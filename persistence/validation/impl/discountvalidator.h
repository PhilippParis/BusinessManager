#ifndef DISCOUNTVALIDATOR_H
#define DISCOUNTVALIDATOR_H

#include <QCoreApplication>
#include <QObject>
#include <memory>

#include "domain/discount.h"
#include "persistence/validation/validator.h"

class DiscountValidator : public Validator<Discount::Ptr>
{
    Q_DECLARE_TR_FUNCTIONS(DiscountValidator)
public:
    DiscountValidator();

    void validateForCreate(Discount::Ptr item) override;
    void validateForUpdate(Discount::Ptr item) override;
    void validateIdentity(Discount::Ptr item) override;

private:
    void validateMandatoryFields(Discount::Ptr item);
};

#endif // DISCOUNTVALIDATOR_H
