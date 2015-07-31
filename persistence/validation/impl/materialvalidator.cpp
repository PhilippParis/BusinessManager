#include "materialvalidator.h"

MaterialValidator::MaterialValidator()
{

}

void MaterialValidator::validateForCreate(Material::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("material must not be null");
    }

    validateMandatoryFields(item);
}

void MaterialValidator::validateForUpdate(Material::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("material must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void MaterialValidator::validateIdentity(Material::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("material must not be null");
    }

    if (item->id() < 0) {
        throw new ValidationException("material must have a valid id");
    }
}

void MaterialValidator::validateMandatoryFields(Material::Ptr item)
{
    if (item->name().isEmpty()) {
        throw new ValidationException(tr("name must not be empty"));
    }
    if (item->costPerUnit() < 0) {
        throw new ValidationException(tr("cost must not be negative"));
    }
    if (item->tax() < 0) {
        throw new ValidationException(tr("tax must not be negative"));
    }
    if (item->unit().isEmpty()) {
        throw new ValidationException(tr("unit must not be empty"));
    }
}
