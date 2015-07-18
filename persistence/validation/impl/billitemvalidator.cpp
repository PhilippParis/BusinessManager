#include "billitemvalidator.h"

BillItemValidator::BillItemValidator()
{

}

bool BillItemValidator::validateForCreate(BillItem::Ptr item)
{
    return validateMandatoryFields(item);
}

bool BillItemValidator::validateForUpdate(BillItem::Ptr item)
{
    return validateMandatoryFields(item) && validateIdentity(item);
}

bool BillItemValidator::validateIdentity(BillItem::Ptr item)
{
    if(item->id() < 0) {
        return false;
    }
}

bool BillItemValidator::validateMandatoryFields(BillItem::Ptr item)
{
    if (item->description().isEmpty()) {
        qDebug()<<"description must not be empty";
        return false;
    }
    if (item->workingHours() < 0) {
        qDebug()<<"working hours must not be negative";
        return false;
    }
    if (item->wagePerHour() < 0) {
        qDebug()<<"wage must not be negative";
        return false;
    }
    if (item->materialCost() < 0) {
        qDebug()<<"material cost must not be negative";
        return false;
    }
    if(item->price() < 0) {
        qDebug()<<"price must not be negative";
        return false;
    }
    if(item->unit().isEmpty()) {
        qDebug()<<"unit must not be empty";
        return false;
    }
    if(item->quantity() <= 0) {
        qDebug()<<"quantity must not be negative";
        return false;
    }

    return true;
}

