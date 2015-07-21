#ifndef BILLITEMVALIDATOR_H
#define BILLITEMVALIDATOR_H

#include <QDebug>
#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/validation/impl/billvalidator.h"
#include "persistence/validation/impl/productvalidator.h"
#include "domain/billitem.h"

class BillItemValidator : public Validator<BillItem::Ptr>
{
public:
    BillItemValidator();

    bool validateForCreate(BillItem::Ptr item) override;
    bool validateForUpdate(BillItem::Ptr item) override;
    bool validateIdentity(BillItem::Ptr item) override;

private:
    bool validateMandatoryFields(BillItem::Ptr item);

private:
    Validator<Bill::Ptr>::Ptr m_billValidator;
    Validator<Product::Ptr>::Ptr m_productValidator;
};

#endif // BILLITEMVALIDATOR_H
