#include "billitemvalidator.h"

BillItemValidator::BillItemValidator()
{
    m_billValidator = std::make_shared<BillValidator>();
    m_productValidator = std::make_shared<ProductValidator>();
}

bool BillItemValidator::validateForCreate(BillItem::Ptr item)
{
    return item != nullptr && validateMandatoryFields(item);
}

bool BillItemValidator::validateForUpdate(BillItem::Ptr item)
{
    return item != nullptr && validateMandatoryFields(item) && validateIdentity(item);
}

bool BillItemValidator::validateIdentity(BillItem::Ptr item)
{
    return item != nullptr && item->id() >= 0;
}

bool BillItemValidator::validateMandatoryFields(BillItem::Ptr item)
{
    if (item->description().isEmpty()) {
        qCDebug(lcValidation) << "description must not be empty";
        return false;
    }
    if (item->workingHours() < 0) {
        qCDebug(lcValidation) << "working hours must not be negative";
        return false;
    }
    if (item->wagePerHour() < 0) {
        qCDebug(lcValidation) << "wage must not be negative";
        return false;
    }
    if (item->materialCost() < 0) {
        qCDebug(lcValidation) << "material cost must not be negative";
        return false;
    }
    if (item->price() < 0) {
        qCDebug(lcValidation) << "price must not be negative";
        return false;
    }
    if (item->unit().isEmpty()) {
        qCDebug(lcValidation) << "unit must not be empty";
        return false;
    }
    if (item->quantity() <= 0) {
        qCDebug(lcValidation) << "quantity must not be negative";
        return false;
    }
    if (!m_billValidator->validateIdentity(item->bill())) {
        qCDebug(lcValidation()) << "bill id must be valid";
        return false;
    }

    QMap<Product::Ptr, double> material = item->material();
    QMap<Product::Ptr, double>::iterator it;

    for (it = material.begin(); it != material.end(); ++it) {
        if (!m_productValidator->validateIdentity(it.key()) || it.value() < 0) {
            qCDebug(lcValidation()) << "materials must be valid";
            return false;
        }
    }

    return true;
}

