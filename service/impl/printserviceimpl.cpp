#include "printserviceimpl.h"

PrintServiceImpl::PrintServiceImpl()
{

}

void PrintServiceImpl::printBill(QPrinter *printer, Bill::Ptr bill)
{
    QPainter *painter = getPainter(printer);

    // draw decoration bar
    printBar(painter);

    // print header
    printHeader(painter, bill->customer(), bill->date());

    // subject and text
    printSubject(painter,
                 tr("Invoice") + " " + QString::number(bill->billNumber()) + " / " + QString::number(bill->date().year()),
                 m_settings.value("docs/billText").toString().split('\n'));

    // bill items
    int currentYPos = printBillItems(printer, painter, bill->items());

    //discount
    currentYPos = printDiscounts(painter, bill->discounts(), currentYPos);

    // total price
    currentYPos = printTotalPrice(painter, bill->inTotalPriceIncludedTaxes(), bill->totalPrice(), currentYPos);

    // footer
    printFooter(printer, painter, currentYPos);
    painter->end();
    delete painter;
}

void PrintServiceImpl::printOffer(QPrinter *printer, Offer::Ptr offer)
{
    QPainter *painter = getPainter(printer);

    // draw decoration bar
    printBar(painter);

    // print header
    printHeader(painter, offer->customer(), QDate::currentDate());

    // subject and text
    printSubject(painter, tr("Offer"), m_settings.value("docs/offerText").toString().split('\n'));

    // items
    int currentYPos = printBillItems(printer, painter, offer->items());

    // total price
    currentYPos = printTotalPrice(painter, offer->inTotalPriceIncludedTaxes(), offer->totalPrice(), currentYPos);

    // footer
    printFooter(printer, painter, currentYPos);
    painter->end();
    delete painter;
}

void PrintServiceImpl::printLetter(QPrinter *printer, Letter::Ptr letter)
{
    QTextDocument *document = letter->textDoc();
    document->setDocumentMargin(500);
    QPainter* painter = getPainter(printer);

    document->documentLayout()->setPaintDevice(printer);
    document->setPageSize(QSizeF(printer->width(), printer->height()));

    printBar(painter);
    printHeader(painter, letter->customer(), QDate::currentDate());

    painter->translate(0, 2100);
    document->drawContents(painter);

    painter->end();
    delete painter;
}

void PrintServiceImpl::printEnvelope(QPrinter *printer, Envelope::Ptr envelope)
{
    QPainter *painter = getPainter(printer);

    QPixmap logo = m_settings.value("docs/logo_envelope").value<QPixmap>();
    if(!logo.isNull()) {
        painter->drawPixmap(50, 120, 1840, 800, logo);
    }

    if(!envelope->withWindow()) {
        // receiver
        printTextBlock(painter, envelope->receiverInfo(), 440, 1500, Qt::AlignLeft);
    }

    QPixmap seal = QPixmap(":/image/seal");
    if(!seal.isNull()) {
        painter->drawPixmap(1600, 500, 500, 500, seal);
    }

    if(printer->pageSize() == QPrinter::A4) { // document format
        //draw cutting lines
        painter->drawLine(QPointF(0, 2400), QPointF(3800, 2400));
        painter->drawLine(QPointF(3800, 2400), QPointF(3800, 0));
    }

    painter->end();
    delete painter;
}

int PrintServiceImpl::printBillItems(QPrinter *printer, QPainter *painter, QList<BillItem::Ptr> items)
{
    // print table header
    printBillItemTableHeader(painter, 3200);

    int currentYPos = 3400;
    for(BillItem::Ptr item : items) {

        //check if item fits on current page
        int itemTextHeight =  item->description().split('\n').count() * 100;
        if(currentYPos + itemTextHeight > 6200) {
            printer->newPage();
            printBar(painter);
            printBillItemTableHeader(painter,600);
            currentYPos = 800;
        }

        printBillItem(painter, item, currentYPos);
        currentYPos += itemTextHeight + 100;
    }

    // draw line
    painter->drawLine(LEFT_MARGIN, currentYPos, RIGHT_MARGIN, currentYPos);
    return currentYPos + 150;
}

void PrintServiceImpl::printBillItemTableHeader(QPainter *painter, int y)
{
    QFont myFont;
    myFont.setPointSizeF(10.0 / SCALE);
    myFont.setBold(true);
    painter->setFont(myFont);

    painter->drawText(5 * 225, y, tr("Article"));
    painter->drawText(9.5 * 225, y, tr("Quantity"));
    painter->drawText(12.5 * 225, y, tr("Price") + "/" + tr("Unit"));
    painter->drawText(3700, y, tr("Total Price"));
    painter->drawLine(LEFT_MARGIN, y + 70, RIGHT_MARGIN, y + 70);

    myFont.setBold(false);
    painter->setFont(myFont);
}

void PrintServiceImpl::printBillItem(QPainter *painter, BillItem::Ptr item, int y)
{
    QFontMetrics fm = painter->fontMetrics();
    QStringList itemDescription = item->description().split('\n');

    //print item description
    printTextBlock(painter, itemDescription, LEFT_MARGIN, y, Qt::AlignLeft);

    //print quantity
    painter->drawText(9.5 * 225, y, QString::number(item->quantity()) + " "+item->unit());

    //print price
    QString price = QString::number(item->price().value(), 'f', 2) + QString::fromUtf8("€");
    painter->drawText(14.5 * 225 - fm.width(price), y, price);

    //print total price
    QString totalPrice = QString::number((item->price() * item->quantity()).value(), 'f', 2) + QString::fromUtf8("€");
    painter->drawText(18 * 225 - fm.width(totalPrice), y, totalPrice);
}

void PrintServiceImpl::printHeader(QPainter *painter, Customer::Ptr receiver, QDate date)
{
    //logo
    if (m_settings.value("docs/show_logo").toBool() && m_settings.value("print/emptyPaper").toBool()) {
        QPixmap logo = m_settings.value("user/logo").value<QPixmap>();
        if (!logo.isNull()) {
            painter->drawPixmap(2500 + 326.6, 110, 2025, 880, logo);
        }
    }

    // receiver
    QStringList receiverInfo;
    receiverInfo << receiver->organisation();
    receiverInfo << receiver->fullName();
    receiverInfo << receiver->street();
    receiverInfo << receiver->city();

    printTextBlock(painter, receiverInfo, LEFT_MARGIN, 1400, Qt::AlignLeft);

    //sender:
    if(m_settings.value("docs/show_sender").toBool() && m_settings.value("print/emptyPaper").toBool()) {
        QStringList senderInfo;
        senderInfo << m_settings.value("user/street").toString();
        senderInfo << m_settings.value("user/city").toString();
        senderInfo << m_settings.value("user/phone").toString();
        senderInfo << m_settings.value("user/mail").toString();
        senderInfo << m_settings.value("user/website").toString();
        senderInfo << "UID Nr: " + m_settings.value("user/uid").toString();

        printTextBlock(painter, senderInfo, RIGHT_MARGIN, 1170, Qt::AlignRight);
    }

    //date
    QFontMetrics fm = painter->fontMetrics();
    QString dateString = date.toString(m_settings.value("docs/date_format").toString());
    painter->drawText(RIGHT_MARGIN - fm.width(dateString), 2500, dateString);
}

void PrintServiceImpl::printFooter(QPrinter *printer, QPainter *painter, int y)
{
    //check if new page
    if(y > 5500) {
        printer->newPage();
        y = 400;
        printBar(painter);
    }

    painter->drawText(LEFT_MARGIN, y, tr("Many Thanks!"));
    y += 200;

    if(m_settings.value("docs/show_signature").toBool()) {
        QPixmap signature = m_settings.value("docs/signature").value<QPixmap>();
        if(!signature.isNull()) {
            painter->drawPixmap(LEFT_MARGIN, y, 1000, 633, signature);
        }
    }

    QFont font = painter->font();
    font.setBold(false);
    font.setPointSizeF(9 / SCALE);
    painter->setFont(font);

    //footer
    if(!m_settings.value("docs/show_footer").toBool()) {
        return;
    }

    QString iban = m_settings.value("user/iban").toString();
    QString bic = m_settings.value("user/bic").toString();
    QString footerLine1 = tr("Banking Account") + "IBAN: " + iban + " BIC: " +
            bic + " | " + m_settings.value("financial/legal_domicile").toString();
    painter->drawText(350, 6500, footerLine1);

    font.setPointSizeF(7 / SCALE);
    painter->setFont(font);
    QStringList footer = m_settings.value("docs/footer").toString().split('\n');
    printTextBlock(painter, footer, 350, 6600, Qt::AlignLeft);

    // "meisterbetrieb" seal
    if (m_settings.value("print/emptyPaper").toBool()) {
        QPixmap seal = QPixmap(":/image/seal");
        if(!seal.isNull()) {
            painter->drawPixmap(4250, 6300, 500, 500, seal);
        }
    }
}

int PrintServiceImpl::printDiscounts(QPainter *painter, QList<Discount::Ptr> discounts, int y)
{
    if(!discounts.isEmpty()) {
        QFontMetrics fm = painter->fontMetrics();
        Discount::Ptr discount = discounts.first();
        painter->drawText(LEFT_MARGIN, y, discount->text());
        QString discountTxt = QString::number((discount->value() * (-1.0)).value(), 'f', 2) + QString::fromUtf8("€");
        painter->drawText(18 * 225 - fm.width(discountTxt), y, discountTxt);
        return y + 150;
    }
    return y;
}

int PrintServiceImpl::printTotalPrice(QPainter *painter, QMap<double, Decimal> taxes, Decimal totalPrice, int y)
{
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);
    QFontMetrics fm = painter->fontMetrics();

    painter->drawText(LEFT_MARGIN, y, tr("Total Price (incl. tax):"));
    QString total = QString::number(totalPrice.value(), 'f', 2) + QString::fromUtf8("€");
    painter->drawText(18 * 225 - fm.width(total), y, total);
    y += 120;

    font.setBold(false);
    font.setPointSizeF(8.0 / SCALE);
    painter->setFont(font);
    fm = painter->fontMetrics();

    QMap<double, Decimal>::iterator i;
    for (i = taxes.begin(); i != taxes.end(); i++) {
        painter->drawText(LEFT_MARGIN, y, tr("Sales Tax (%1 %):").arg(QString::number(i.key() * 100)));
        QString tax = QString::number(i.value().value(), 'f', 2) + QString::fromUtf8("€");
        painter->drawText(18 * 225 - fm.width(tax), y, tax);
        y += 100;
    }

    font.setPointSizeF(1.0 / SCALE);
    painter->setFont(font);

    return y + 150;
}

void PrintServiceImpl::printSubject(QPainter *painter, QString subject, QStringList text)
{
    // subject
    painter->drawText(LEFT_MARGIN, 2600, subject);

    // text below subject
    printTextBlock(painter, text, LEFT_MARGIN, 2800, Qt::AlignLeft);
}

void PrintServiceImpl::printTextBlock(QPainter *painter, QStringList text, int x, int y, Qt::AlignmentFlag align)
{
    QFontMetrics fm = painter->fontMetrics();
    for(QString line : text) {
        if(align == Qt::AlignLeft) {
            painter->drawText(x, y, line);
        } else {
            painter->drawText(x - fm.width(line), y, line);
        }
        y += 100;
    }
}

QPainter* PrintServiceImpl::getPainter(QPrinter *printer)
{
    //set up painter
    QPainter *painter = new QPainter();
    painter->begin(printer);

    painter->scale(SCALE, SCALE);

    QBrush brush;
    QColor col = QColor(m_settings.value("docs/color").value<QColor>());

    brush.setColor(col);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);

    QFont myFont;
    myFont.setPointSizeF(10.0 / SCALE);
    painter->setFont(myFont);
    return painter;
}

void PrintServiceImpl::printBar(QPainter *painter)
{
    if(m_settings.value("docs/show_bar").toBool() && m_settings.value("print/emptyPaper").toBool()) {
        painter->setPen(QColor(255,204,102));
        painter->drawRect(50, 0, 184, 6800);
        painter->setPen(Qt::black);
    }
}

