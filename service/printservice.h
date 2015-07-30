#ifndef PRINTSERVICE_H
#define PRINTSERVICE_H

#include <QPrinter>
#include <memory.h>

#include "domain/bill.h"
#include "domain/offer.h"
#include "domain/letter.h"
#include "domain/envelope.h"

class PrintService
{
public:
    typedef std::shared_ptr<PrintService> Ptr;
    PrintService();

    virtual void printBill(QPrinter *printer, Bill::Ptr bill) = 0;
    virtual void printOffer(QPrinter *printer, Offer::Ptr offer) = 0;
    virtual void printLetter(QPrinter *printer, Letter::Ptr letter) = 0;
    virtual void printEnvelope(QPrinter *printer, Envelope::Ptr letter) = 0;
};

#endif // PRINTSERVICE_H
