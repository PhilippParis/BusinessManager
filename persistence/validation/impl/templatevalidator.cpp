#include "templatevalidator.h"

TemplateValidator::TemplateValidator()
{
    m_materialValidator = std::make_shared<MaterialValidator>();
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
        throw new ValidationException(tr("name must not be empty"));
    }
    if (item->itemDesc().isEmpty()) {
        throw new ValidationException(tr("item desc must not be empty"));
    }
    if (item->unit().isEmpty()) {
        throw new ValidationException(tr("unit must not be empty"));
    }
    if (item->price() < 0 ) {
        throw new ValidationException(tr("price must not be negative"));
    }
    if (item->workingHours() < 0 ) {
        throw new ValidationException(tr("working hours must not be negative"));
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

