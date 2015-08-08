#ifndef OFFERVALIDATOR_H
#define OFFERVALIDATOR_H

#include <memory>

#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/validation/impl/customervalidator.h"
#include "persistence/validation/impl/billitemvalidator.h"
#include "domain/offer.h"

class OfferValidator : public Validator<Offer::Ptr>
{
    Q_DECLARE_TR_FUNCTIONS(BillValidator)
public:
    OfferValidator();

    void validateForCreate(Offer::Ptr item) override;
    void validateForUpdate(Offer::Ptr item) override;
    void validateIdentity(Offer::Ptr item) override;

private:
    void validateMandatoryFields(Offer::Ptr item);

private:
    Validator<Customer::Ptr>::Ptr m_customerValidator;
    Validator<BillItem::Ptr>::Ptr m_billItemValidator;
};

#endif // OFFERVALIDATOR_H
