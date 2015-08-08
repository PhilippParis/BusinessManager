#include "offerserviceimpl.h"

OfferServiceImpl::OfferServiceImpl(OfferDAO::Ptr offerDAO, OfferItemDAO::Ptr offerItemDAO,
                                   Validator<Offer::Ptr>::Ptr offerValidator, Validator<BillItem::Ptr>::Ptr billItemValidator)
 : m_offerDAO(offerDAO),
   m_offerItemDAO(offerItemDAO),
   m_offerValidator(offerValidator),
   m_billItemValidator(billItemValidator)
{

}

void OfferServiceImpl::add(Offer::Ptr offer)
{
    try {
        for(BillItem::Ptr item : offer->items()) {
            addItem(item);
        }

        m_offerValidator->validateForCreate(offer);
        m_offerDAO->create(offer);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void OfferServiceImpl::update(Offer::Ptr offer)
{
    try {
        for(BillItem::Ptr item : offer->items()) {
            if(item->id() < 0) {
                addItem(item);
            } else {
                updateItem(item);
            }
        }

        m_offerValidator->validateForUpdate(offer);
        m_offerDAO->update(offer);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void OfferServiceImpl::remove(Offer::Ptr offer)
{
    try {
        m_offerValidator->validateIdentity(offer);
        m_offerDAO->remove(offer);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

Offer::Ptr OfferServiceImpl::get(int id)
{
    try {
        return m_offerDAO->get(id);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

QList<Offer::Ptr> OfferServiceImpl::getAll()
{
    try {
        return m_offerDAO->getAll();
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

void OfferServiceImpl::addItem(BillItem::Ptr item)
{
    try {
        m_billItemValidator->validateForCreate(item);
        m_offerItemDAO->create(item);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void OfferServiceImpl::updateItem(BillItem::Ptr item)
{
    try {
        m_billItemValidator->validateForUpdate(item);
        m_offerItemDAO->update(item);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void OfferServiceImpl::removeItem(BillItem::Ptr item)
{
    try {
        m_billItemValidator->validateIdentity(item);
        m_offerItemDAO->remove(item);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

Validator<BillItem::Ptr>::Ptr OfferServiceImpl::billItemValidator()
{
    return m_billItemValidator;
}

Validator<Offer::Ptr>::Ptr OfferServiceImpl::offerValidator()
{
    return m_offerValidator;
}



