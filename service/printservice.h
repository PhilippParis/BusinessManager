#ifndef PRINTSERVICE_H
#define PRINTSERVICE_H

#include <QPrinter>
#include <memory.h>

#include "domain/bill.h"

class PrintService
{
public:
    typedef std::shared_ptr<PrintService> Ptr;
    PrintService();

    virtual void printBill(QPrinter *printer, Bill::Ptr bill) = 0;
};

#endif // PRINTSERVICE_H
