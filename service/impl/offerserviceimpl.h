#ifndef OFFERSERVICEIMPL_H
#define OFFERSERVICEIMPL_H

#include "service/offerservice.h"

#include "persistence/offerdao.h"
#include "persistence/offeritemdao.h"

#include "service/serviceexception.h"

class OfferServiceImpl : public OfferService
{
public:
    OfferServiceImpl(OfferDAO::Ptr offerDAO, OfferItemDAO::Ptr offerItemDAO,
                     Validator<Offer::Ptr>::Ptr offerValidator, Validator<BillItem::Ptr>::Ptr billItemValidator);

    void add(Offer::Ptr bill) override;
    void update(Offer::Ptr bill) override;
    void remove(Offer::Ptr bill) override;
    Offer::Ptr get(int id) override;
    QList<Offer::Ptr> getAll() override;

    Validator<BillItem::Ptr>::Ptr billItemValidator() override;
    Validator<Offer::Ptr>::Ptr offerValidator() override;

private:
    void addItem(BillItem::Ptr item);
    void updateItem(BillItem::Ptr item);
    void removeItem(BillItem::Ptr item);

private:
    OfferDAO::Ptr m_offerDAO;
    OfferItemDAO::Ptr m_offerItemDAO;

    Validator<Offer::Ptr>::Ptr m_offerValidator;
    Validator<BillItem::Ptr>::Ptr m_billItemValidator;
};

#endif // OFFERSERVICEIMPL_H
