#ifndef MATERIALVALIDATOR_H
#define MATERIALVALIDATOR_H

#include <QCoreApplication>
#include <memory>

#include "logging.h"

#include "domain/material.h"
#include "persistence/validation/validator.h"

class MaterialValidator : public Validator<Material::Ptr>
{
    Q_DECLARE_TR_FUNCTIONS(MaterialValidator)
public:
    MaterialValidator();

    void validateForCreate(Material::Ptr item) override;
    void validateForUpdate(Material::Ptr item) override;
    void validateIdentity(Material::Ptr item) override;

private:
    void validateMandatoryFields(Material::Ptr item);
};

#endif // MATERIALVALIDATOR_H
