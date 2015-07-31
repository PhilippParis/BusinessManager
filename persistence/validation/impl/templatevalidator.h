#ifndef TEMPLATEVALIDATOR_H
#define TEMPLATEVALIDATOR_H

#include <QCoreApplication>

#include "domain/template.h"
#include "persistence/validation/validator.h"
#include "persistence/validation/impl/materialvalidator.h"

class TemplateValidator : public Validator<Template::Ptr>
{
    Q_DECLARE_TR_FUNCTIONS(TemplateValidator)
public:
    TemplateValidator();

    void validateForCreate(Template::Ptr item) override;
    void validateForUpdate(Template::Ptr item) override;
    void validateIdentity(Template::Ptr item) override;

private:
    void validateMandatoryFields(Template::Ptr item);

private:
    Validator<Material::Ptr>::Ptr m_materialValidator;
};

#endif // TEMPLATEVALIDATOR_H
