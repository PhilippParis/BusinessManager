#ifndef OFFERSERVICE_H
#define OFFERSERVICE_H

#include "domain/offer.h"
#include "persistence/validation/validator.h"

class OfferService
{
public:
    typedef std::shared_ptr<OfferService> Ptr;
    OfferService();

    /**
     * @brief adds the offer to the underlying datasource
     * @param offer offer to add
     */
    virtual void add(Offer::Ptr offer) = 0;

    /**
     * @brief updates the offer in the underlying datasource
     * @param offer offer to update
     */
    virtual void update(Offer::Ptr offer) = 0;

    /**
     * @brief removes the offer from the underlying datasource
     * @param offer to remove
     */
    virtual void remove(Offer::Ptr offer) = 0;

    /**
     * @param id id of the offer
     * @return returns the offer with the specified id
     */
    virtual Offer::Ptr get(int id) = 0;

    /**
     * @return returns all offers
     */
    virtual QList<Offer::Ptr> getAll() = 0;

    /**
     * @return returns the billitem validator
     */
    virtual Validator<BillItem::Ptr>::Ptr billItemValidator() = 0;

    /**
     * @return returns the offer validator
     */
    virtual Validator<Offer::Ptr>::Ptr offerValidator() = 0;
};


#endif // OFFERSERVICE_H
