#ifndef OFFERSERVICE_H
#define OFFERSERVICE_H

#include "domain/offer.h"
#include "persistence/validation/validator.h"

class OfferService
{
public:
    typedef std::shared_ptr<OfferService> Ptr;
    OfferService();

    virtual void add(Offer::Ptr offer) = 0;
    virtual void update(Offer::Ptr offer) = 0;
    virtual void remove(Offer::Ptr offer) = 0;
    virtual Offer::Ptr get(int id) = 0;
    virtual QList<Offer::Ptr> getAll() = 0;

    virtual Validator<BillItem::Ptr>::Ptr billItemValidator() = 0;
    virtual Validator<Offer::Ptr>::Ptr offerValidator() = 0;
};


#endif // OFFERSERVICE_H
