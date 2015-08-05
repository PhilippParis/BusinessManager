#include "billitemvalidator.h"

BillItemValidator::BillItemValidator()
{
    m_materialValidator = std::make_shared<MaterialValidator>();
}

void BillItemValidator::validateForCreate(BillItem::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("item must not be null");
    }

    validateMandatoryFields(item);
}

void BillItemValidator::validateForUpdate(BillItem::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("item must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void BillItemValidator::validateIdentity(BillItem::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("item must not be null");
    }
    if (item->id() < 0) {
        throw new ValidationException("item must have a valid id");
    }
}

void BillItemValidator::validateMandatoryFields(BillItem::Ptr item)
{
    if (item->description() == nullptr || item->description().isEmpty()) {
        throw new ValidationException(tr("description must not be empty"));
    }
    if (item->workingHours() < 0.0) {
        throw new ValidationException(tr("working hours must not be negative"));
    }
    if (item->wagePerHour() < Decimal::fromValue(0.0)) {
        throw new ValidationException(tr("wage must not be negative"));
    }
    if (item->materialCost() < Decimal::fromValue(0.0)) {
        throw new ValidationException(tr("material cost must not be negative"));
    }
    if (item->price() < Decimal::fromValue(0.0)) {
        throw new ValidationException(tr("price must not be negative"));
    }
    if (item->unit() == nullptr || item->unit().isEmpty()) {
        throw new ValidationException(tr("unit must not be empty"));
    }
    if (item->quantity() <= 0.0) {
        throw new ValidationException(tr("quantity must not be negative"));
    }
    if (item->materialOverhead() < 0.0 || item->materialOverhead() > 1.0) {
        throw new ValidationException(tr("material overhead must be between 0% and 100%"));
    }
    if (item->factoryOverhead() < 0.0 || item->factoryOverhead() > 1.0) {
        throw new ValidationException(tr("factory overhead must be between 0% and 100%"));
    }
    if (item->taxRate() < 0.0 || item->taxRate() > 1.0) {
        throw new ValidationException(tr("tax must be between 0% and 100%"));
    }
    if (item->cashback() < 0.0 || item->cashback() > 1.0) {
        throw new ValidationException(tr("cashback must be between 0% and 100%"));
    }
    if (item->profit() < 0.0 || item->profit() > 1.0) {
        throw new ValidationException(tr("profit must be between 0% and 100%"));
    }

    QMap<Material::Ptr, double> material = item->material();
    QMap<Material::Ptr, double>::iterator it;

    for (it = material.begin(); it != material.end(); ++it) {
        m_materialValidator->validateIdentity(it.key());

        if (it.value() < 0) {
            throw new ValidationException(tr("material quantity must not be negative"));
        }
    }
}

