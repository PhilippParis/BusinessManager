#include "billitemvalidator.h"

BillItemValidator::BillItemValidator()
{
    m_productValidator = std::make_shared<ProductValidator>();
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
        throw new ValidationException("description must not be empty");
    }
    if (item->workingHours() < 0) {
        throw new ValidationException("working hours must not be negative");
    }
    if (item->wagePerHour() < 0) {
        throw new ValidationException("wage must not be negative");
    }
    if (item->materialCost() < 0) {
        throw new ValidationException("material cost must not be negative");
    }
    if (item->price() < 0) {
        throw new ValidationException("price must not be negative");
    }
    if (item->unit() == nullptr || item->unit().isEmpty()) {
        throw new ValidationException("unit must not be empty");
    }
    if (item->quantity() <= 0) {
        throw new ValidationException("quantity must not be negative");
    }

    QMap<Product::Ptr, double> material = item->material();
    QMap<Product::Ptr, double>::iterator it;

    for (it = material.begin(); it != material.end(); ++it) {
        m_productValidator->validateIdentity(it.key());

        if (it.value() < 0) {
            throw new ValidationException("material quantity must not be negative");
        }
    }
}

