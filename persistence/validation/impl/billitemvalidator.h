#ifndef BILLITEMVALIDATOR_H
#define BILLITEMVALIDATOR_H

#include <QDebug>

#include "persistence/validation/validator.h"
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
};

#endif // BILLITEMVALIDATOR_H
