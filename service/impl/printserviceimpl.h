#ifndef PRINTSERVICEIMPL_H
#define PRINTSERVICEIMPL_H

#include <QCoreApplication>
#include <QSettings>
#include <QPainter>
#include <QDate>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

#include "domain/bill.h"
#include "domain/customer.h"

#include "service/printservice.h"

#define LEFT_MARGIN (440)
#define RIGHT_MARGIN (4400)

#ifdef Q_OS_LINUX
#define SCALE (2.0)
#else
#define SCALE (1.0)
#endif

class PrintServiceImpl : public PrintService
{
    Q_DECLARE_TR_FUNCTIONS(PrintServiceImpl)
public:
    PrintServiceImpl();
    void printBill(QPrinter *printer, Bill::Ptr bill) override;
    void printOffer(QPrinter *printer, Offer::Ptr offer) override;
    void printLetter(QPrinter *printer, Letter::Ptr letter) override;
    void printEnvelope(QPrinter *printer, Envelope::Ptr envelope) override;

private:
    void printSubject(QPainter *painter, QString subject, QStringList text);
    int printBillItems(QPrinter *printer, QPainter *painter, QList<BillItem::Ptr> items);
    void printBillItemTableHeader(QPainter *painter, int y);
    void printBillItem(QPainter *painter, BillItem::Ptr item, int y);
    void printHeader(QPainter *painter, Customer::Ptr receiver, QDate date);
    void printTextBlock(QPainter *painter, QStringList text, int x, int y, Qt::AlignmentFlag align);
    void printBar(QPainter *painter);
    void printFooter(QPrinter *printer, QPainter *painter, int y);
    int printDiscounts(QPainter *painter, QList<Discount::Ptr> discounts, int y);
    int printTotalPrice(QPainter *painter, double price, int y);

    QPainter* getPainter(QPrinter *printer);

private:
    QSettings m_settings;
};

#endif // PRINTSERVICEIMPL_H
