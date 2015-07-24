#include "billitemwizard.h"
#include "ui_billitemwizard.h"

BillItemWizard::BillItemWizard(QWidget *parent, BillService::Ptr billService,
                               ProductService::Ptr productService, TemplateService::Ptr templateService) :
    QWizard(parent),
    ui(new Ui::BillItemWizard),
    m_billService(billService),
    m_productService(productService),
    m_templateService(templateService)
{
    ui->setupUi(this);
}

BillItemWizard::~BillItemWizard()
{
    delete ui;
}

void BillItemWizard::prepareForCreate()
{
    m_openMode = Create;
    ui->sbPricePerUnit->setValue(0.0);
    ui->lblCostPerArticle->setText("0.00€");
    ui->leSearchTemplate->clear();
    ui->leTemplateName->clear();
    ui->leTemplateOrg->clear();
    ui->leUnit->clear();
    ui->textEditArticleDesc->clear();
    ui->sbQuantity->setValue(0.0);
    ui->sbWorkingHours->setValue(0.0);
}

void BillItemWizard::prepareForUpdate(BillItem::Ptr item)
{
    m_openMode = Update;
    double cost = item->materialCost() + item->workingHours() * item->wagePerHour();

    m_id = item->id();

    ui->sbPricePerUnit->setValue(item->price());
    ui->leSearchTemplate->clear();
    ui->leTemplateName->clear();
    ui->leTemplateOrg->clear();
    ui->textEditArticleDesc->setText(item->description());
    ui->leUnit->setText(item->unit());
    ui->sbQuantity->setValue(item->quantity());
    ui->sbWorkingHours->setValue(item->workingHours());
    ui->lblCostPerArticle->setText(QString::number(cost) + QString::fromUtf8("€"));
    // TODO display wage
}

BillItem::Ptr BillItemWizard::toDomainObject()
{
    BillItem::Ptr item = std::make_shared<BillItem>();

    item->setId(m_id);
    item->setDescription(ui->textEditArticleDesc->toPlainText());
    item->setMaterialCost(materialCosts());
    item->setPrice(ui->sbPricePerUnit->value());
    item->setQuantity(ui->sbQuantity->value());
    item->setUnit(ui->leUnit->text());
    item->setWorkingHours(ui->sbWorkingHours->value());
    // TODO set wage

    return item;
}

void BillItemWizard::on_textEditArticleDesc_textChanged()
{
    QFont tmp;
    tmp.setPointSizeF(12.0);
    QFontMetrics fm = QFontMetrics(tmp);

    if(fm.width(ui->textEditArticleDesc->textCursor().block().text()) > 250) {
        QTextCursor cursor = ui->textEditArticleDesc->textCursor();
        cursor.movePosition(QTextCursor::PreviousWord);

        if(cursor.positionInBlock() == 0) {
            // prev. word is longer than a line -> force user to split the word
            cursor.movePosition(QTextCursor::End);
            cursor.deletePreviousChar();
        } else {
            // prev word is shorter than the line -> move word to the next line
            cursor.insertText("\n");
            cursor.movePosition(QTextCursor::End);
        }
    }
}

void BillItemWizard::accept()
{
    BillItem::Ptr item = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_billService->addItem(item);
        } else {
            m_billService->updateItem(item);
        }
        m_id = item->id();
        QWizard::accept();
    } catch (ServiceException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
        delete e;
    }
}

double BillItemWizard::materialCosts()
{
    return 0.0; // TODO
}
