#ifndef BILLITEMVALIDATOR_H
#define BILLITEMVALIDATOR_H

#include <QDebug>
#include <QCoreApplication>
#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/validation/impl/billvalidator.h"
#include "persistence/validation/impl/materialvalidator.h"
#include "domain/billitem.h"

class BillItemValidator : public Validator<BillItem::Ptr>
{
    Q_DECLARE_TR_FUNCTIONS(BillItemValidator)
public:
    BillItemValidator();

    void validateForCreate(BillItem::Ptr item) override;
    void validateForUpdate(BillItem::Ptr item) override;
    void validateIdentity(BillItem::Ptr item) override;

private:
    void validateMandatoryFields(BillItem::Ptr item);

private:
    Validator<Material::Ptr>::Ptr m_materialValidator;
};

#endif // BILLITEMVALIDATOR_H
