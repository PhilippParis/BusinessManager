#ifndef TEMPLATEVALIDATOR_H
#define TEMPLATEVALIDATOR_H

#include "domain/template.h"
#include "persistence/validation/validator.h"

class TemplateValidator : public Validator<Template::Ptr>
{
public:
    TemplateValidator();

    void validateForCreate(Template::Ptr item) override;
    void validateForUpdate(Template::Ptr item) override;
    void validateIdentity(Template::Ptr item) override;

private:
    void validateMandatoryFields(Template::Ptr item);
};

#endif // TEMPLATEVALIDATOR_H
