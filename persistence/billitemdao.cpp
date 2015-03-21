#include "billitemdao.h"

BillItemDAO::BillItemDAO()
{

}

BillItemDAO::~BillItemDAO()
{

}

bool BillItemDAO::write(BillItem::Ptr item)
{
    if(m_dataBuffer.contains(item->id())) {
        // item already stored
        return false;
    }

    if(!writeToDataSource(item)) {
        // writing failed
        return false;
    }

    m_dataBuffer.insert(item->id(), item);
}

bool BillItemDAO::update(BillItem::Ptr item)
{
    if(!updateInDataSource(item)) {
        return false;
    }

    if(m_dataBuffer.contains(item->id())) {
        // update data buffer
        BillItem::Ptr bufferedItem = m_dataBuffer.value(item->id());
        bufferedItem->setDescription(item->description());
        bufferedItem->setMaterialCost(item->materialCost());
        bufferedItem->setPrice(item->price());
        bufferedItem->setUnit(item->unit());
        bufferedItem->setWagePerHour(item->wagePerHour());
        bufferedItem->setWorkingHours(item->workingHours());
    }
}

bool BillItemDAO::remove(BillItem::Ptr item)
{
    if(!removeFromDataSource(item)) {
        return false;
    }

    m_dataBuffer.remove(item->id());
    return true;
}

BillItem::Ptr BillItemDAO::get(int id)
{
    BillItem::Ptr item = getFromDataSource(id);
    if(item == nullptr) {
        return nullptr;
    }

    m_dataBuffer.insert(id, item);
    return item;
}

