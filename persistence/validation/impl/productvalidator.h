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

    void validateForCreate(Product::Ptr item) override;
    void validateForUpdate(Product::Ptr item) override;
    void validateIdentity(Product::Ptr item) override;

private:
    void validateMandatoryFields(Product::Ptr item);
};

#endif // PRODUCTVALIDATOR_H
