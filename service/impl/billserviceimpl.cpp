#include "billserviceimpl.h"

BillServiceImpl::BillServiceImpl(BillDAO::Ptr billDAO, BillItemDAO::Ptr billItemDAO,
                         Validator<Bill::Ptr>::Ptr billValidator, Validator<BillItem::Ptr>::Ptr billItemValidator)
 : m_billDAO(billDAO),
   m_billItemDAO(billItemDAO),
   m_billValidator(billValidator),
   m_billItemValidator(billItemValidator)
{

}

void BillServiceImpl::addBill(Bill::Ptr bill)
{
    try {
        m_billValidator->validateForCreate(bill);
        m_billDAO->create(bill);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void BillServiceImpl::updateBill(Bill::Ptr bill)
{
    try {
        m_billValidator->validateForUpdate(bill);
        m_billDAO->update(bill);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void BillServiceImpl::removeBill(Bill::Ptr bill)
{
    try {
        m_billValidator->validateIdentity(bill);
        m_billDAO->remove(bill);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

Bill::Ptr BillServiceImpl::getBill(int id)
{
    try {
        return m_billDAO->get(id);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

QList<Bill::Ptr> BillServiceImpl::getAllBills()
{
    try {
        return m_billDAO->getAll();
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

void BillServiceImpl::addItem(BillItem::Ptr item)
{
    try {
        m_billItemValidator->validateForCreate(item);
        m_billItemDAO->create(item);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void BillServiceImpl::updateItem(BillItem::Ptr item)
{
    try {
        m_billItemValidator->validateForUpdate(item);
        m_billItemDAO->update(item);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

void BillServiceImpl::removeItem(BillItem::Ptr item)
{
    try {
        m_billItemValidator->validateIdentity(item);
        m_billItemDAO->remove(item);
    } catch (Exception *e) {
        throw new ServiceException(e);
    }
}

BillItem::Ptr BillServiceImpl::getItem(int id)
{
    try {
        return m_billItemDAO->get(id);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}

QList<BillItem::Ptr> BillServiceImpl::getItemsOfBill(int billID)
{
    try {
        return m_billItemDAO->getItemsOfBill(billID);
    } catch (PersistenceException *e) {
        throw new ServiceException(e);
    }
}
