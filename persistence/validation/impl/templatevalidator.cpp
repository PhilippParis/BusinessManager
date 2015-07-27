#include "templatevalidator.h"

TemplateValidator::TemplateValidator()
{

}

void TemplateValidator::validateForCreate(Template::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("template must not be null");
    }

    validateMandatoryFields(item);
}

void TemplateValidator::validateForUpdate(Template::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("template must not be null");
    }

    validateMandatoryFields(item);
    validateIdentity(item);
}

void TemplateValidator::validateIdentity(Template::Ptr item)
{
    if (item == nullptr) {
        throw new ValidationException("template must not be null");
    }

    if (item->id() < 0) {
        throw new ValidationException("template must have a valid id");
    }
}

void TemplateValidator::validateMandatoryFields(Template::Ptr item)
{
    if (item->name().isEmpty()) {
        throw new ValidationException("name must not be empty");
    }
    if (item->itemDesc().isEmpty()) {
        throw new ValidationException("item desc must not be empty");
    }
    if (item->unit().isEmpty()) {
        throw new ValidationException("unit must not be empty");
    }
    if (item->price() < 0 ) {
        throw new ValidationException("price must not be negative");
    }
    if (item->workingHours() < 0 ) {
        throw new ValidationException("working hours must not be negative");
    }
}

