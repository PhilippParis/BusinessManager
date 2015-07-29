#include "printserviceimpl.h"

PrintServiceImpl::PrintServiceImpl()
{

}

void PrintServiceImpl::printBill(QPrinter *printer, Bill::Ptr bill)
{
    QPainter *painter = getPainter(printer);
    QFontMetrics fm = painter->fontMetrics();

    // draw decoration bar
    printBar(painter);

    // print header
    printHeader(painter, bill->customer(), bill->date());

    // subject
    painter->drawText(LEFT_MARGIN, 2600, tr("Invoice") + " " +
                      QString::number(bill->billNumber()) + " / " +
                      QString::number(bill->date().year()));

    // bill text (below subject)
    QStringList txt = m_settings.value("docs/billText").toString().split('\n');
    printTextBlock(painter, txt, LEFT_MARGIN, 2800, Qt::AlignLeft);

    // print table header
    printBillItemTableHeader(painter, 3200);

    int currentYPos = 3400;
    for(BillItem::Ptr item : bill->items()) {

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
    currentYPos += 150;

    //discount
    if(!bill->discounts().isEmpty()) {
        Discount::Ptr discount = bill->discounts().first();
        painter->drawText(LEFT_MARGIN, currentYPos, discount->text());
        QString discountTxt = QString::number(discount->value() * (-1.0), 'f', 2) + QString::fromUtf8("€");
        painter->drawText(18 * 225 - fm.width(discountTxt), currentYPos, discountTxt);
        currentYPos += 150;
    }

    //total sum
    QFont font = painter->font();
    font.setBold(true);
    painter->setFont(font);
    fm = painter->fontMetrics();
    painter->drawText(LEFT_MARGIN, currentYPos, tr("Total Amount:"));

    QString total = QString::number(bill->totalPrice(), 'f', 2) + QString::fromUtf8("€");
    painter->drawText(18 * 225 - fm.width(total), currentYPos, total);
    currentYPos += 250;

    //check if new page
    if(currentYPos > 5500) {
        printer->newPage();
        currentYPos = 400;
        printBar(painter);
    }

    // footer
    printFooter(painter, currentYPos);
    painter->end();
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
    QString price = QString::number(item->price(), 'f', 2) + QString::fromUtf8("€");
    painter->drawText(14.5 * 225 - fm.width(price), y, price);

    //print total price
    QString totalPrice = QString::number(item->price() * item->quantity(), 'f', 2) + QString::fromUtf8("€");
    painter->drawText(18 * 225 - fm.width(totalPrice), y, totalPrice);
}

void PrintServiceImpl::printHeader(QPainter *painter, Customer::Ptr receiver, QDate date)
{
    //logo
    if (m_settings.value("docs/show_logo").toBool()) {
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
    if(m_settings.value("docs/show_sender").toBool()) {
        QStringList senderInfo;
        senderInfo << m_settings.value("user/street").toString();
        senderInfo << m_settings.value("user/city").toString();
        senderInfo << m_settings.value("user/phone").toString();
        senderInfo << m_settings.value("user/mail").toString();
        senderInfo << m_settings.value("user/website").toString();

        printTextBlock(painter, senderInfo, RIGHT_MARGIN, 1170, Qt::AlignRight);
    }

    //date
    QFontMetrics fm = painter->fontMetrics();
    QString dateString = date.toString(m_settings.value("docs/date_format").toString());
    painter->drawText(RIGHT_MARGIN - fm.width(dateString), 2500, dateString);
}

void PrintServiceImpl::printFooter(QPainter *painter, int y)
{
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
    QPixmap seal = QPixmap(":/icon/images/seal.jpg");
    if(!seal.isNull()) {
        painter->drawPixmap(4250, 6300, 500, 500, seal);
    }
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
    if(m_settings.value("docs/show_bar").toBool()) {
        painter->setPen(QColor(255,204,102));
        painter->drawRect(50, 0, 184, 6800);
        painter->setPen(Qt::black);
    }
}
