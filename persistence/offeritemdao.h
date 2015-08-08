#ifndef OFFERITEMDAO_H
#define OFFERITEMDAO_H

#include <memory>
#include "itemdao.h"

class OfferItemDAO : public ItemDAO
{
public:
    typedef std::shared_ptr<OfferItemDAO> Ptr;
    OfferItemDAO();

    /**
     * @param offerID id of the offer
     * @return returns all items of a offer
     */
    virtual QList<BillItem::Ptr> getItemsOfOffer(int offerID) = 0;
};

#endif // OFFERITEMDAO_H
