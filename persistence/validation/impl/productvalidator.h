#ifndef PRODUCTVALIDATOR_H
#define PRODUCTVALIDATOR_H

#include <memory>

#include "logging.h"

#include "domain/product.h"
#include "persistence/validation/validator.h"

class ProductValidator : public Validator<Product::Ptr>
{
public:
    ProductValidator();

    bool validateForCreate(Product::Ptr item) override;
    bool validateForUpdate(Product::Ptr item) override;
    bool validateIdentity(Product::Ptr item) override;

private:
    bool validateMandatoryFields(Product::Ptr item);
};

#endif // PRODUCTVALIDATOR_H
