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

    /**
     * @brief prints the bill
     * @param printer printer
     * @param bill bill to print
     */
    virtual void printBill(QPrinter *printer, Bill::Ptr bill) = 0;

    /**
     * @brief prints the offer
     * @param printer printer
     * @param offer offer to print
     */
    virtual void printOffer(QPrinter *printer, Offer::Ptr offer) = 0;

    /**
     * @brief prints the letter
     * @param printer printer
     * @param letter letter to print
     */
    virtual void printLetter(QPrinter *printer, Letter::Ptr letter) = 0;

    /**
     * @brief prints the envelope
     * @param printer printer
     * @param envelope envelope to print
     */
    virtual void printEnvelope(QPrinter *printer, Envelope::Ptr envelope) = 0;
};

#endif // PRINTSERVICE_H
