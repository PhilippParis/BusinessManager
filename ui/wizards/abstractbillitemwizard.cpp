#include "abstractbillitemwizard.h"
#include "ui_abstractbillitemwizard.h"

AbstractBillItemWizard::AbstractBillItemWizard(QWidget *parent, MaterialService::Ptr materialService, TemplateService::Ptr templateService)
    : QWizard(parent),
      ui(new Ui::AbstractBillItemWizard),
      m_materialService(materialService),
      m_templateService(templateService)
{
    ui->setupUi(this);
    QSettings settings;

    m_materialModel = new MaterialTableModel();
    SpinBoxDelegate* delegate = new SpinBoxDelegate(ui->tblMaterial);
    ui->tblMaterial->setModel(m_materialModel);
    ui->tblMaterial->setItemDelegateForColumn(5, delegate);

    ui->sbTaxRate->setValue(settings.value("financial/tax").toDouble() * 100.0);
    connect(m_materialModel, SIGNAL(materialChanged()), SLOT(updateMaterialCosts()));
}

AbstractBillItemWizard::~AbstractBillItemWizard()
{
    delete ui;
    delete m_materialModel;
}

void AbstractBillItemWizard::prepareForCreate(Template::Ptr templ)
{
    m_openMode = Create;

    ui->sbPricePerUnit->setValue(0.0);
    ui->leTemplateName->clear();
    ui->leTemplateOrg->clear();
    ui->leUnit->clear();
    ui->textEditArticleDesc->clear();
    ui->sbQuantity->setValue(0.0);
    ui->sbWorkingHours->setValue(0.0);

    displayTemplateData(templ);
}

void AbstractBillItemWizard::on_textEditArticleDesc_textChanged()
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

void AbstractBillItemWizard::accept()
{
    if ((m_openMode == Create && onCreate()) || (m_openMode == Update && onUpdate())) {
        QWizard::accept();
    }
}

void AbstractBillItemWizard::on_btnAddMaterial_clicked()
{
    MaterialSelectionDialog *dialog = new MaterialSelectionDialog(this, m_materialService);
    connect(dialog, SIGNAL(materialAdded(Material::Ptr)), this, SIGNAL(materialAdded(Material::Ptr)));
    if(dialog->exec() == QDialog::Accepted) {
        m_materialModel->add(dialog->selectedMaterial(), dialog->quantity());
    }
}

void AbstractBillItemWizard::on_btnDeleteMaterial_clicked()
{
    m_materialModel->remove(m_materialModel->get(ui->tblMaterial->currentIndex()));
}

void AbstractBillItemWizard::updateMaterialCosts()
{
    QMap<Material::Ptr, double> items = m_materialModel->itemsWithQuantity();
    m_materialCost = Decimal::fromValue(0.0);
    m_materialNetCost = Decimal::fromValue(0.0);

    QMap<Material::Ptr, double>::iterator it;
    for(it = items.begin(); it != items.end(); ++it) {
        m_materialNetCost += it.key()->netCostPerUnit() * it.value();
        m_materialCost += it.key()->costPerUnit() * it.value();
    }

    QSettings settings;
    if (!settings.value("financial/preTaxEligible").toBool()) {
        m_materialNetCost = m_materialCost;
    }
}

void AbstractBillItemWizard::on_sbPricePerUnit_valueChanged(double value)
{
    BillItem::Ptr item = toBillItem();

    QPalette palette;
    palette.setColor(QPalette::Text, value < item->costs().value() ? Qt::red : Qt::black);
    ui->sbPricePerUnit->setPalette(palette);
}

void AbstractBillItemWizard::on_btnAuto_clicked()
{
    BillItem::Ptr item = toBillItem();
    ui->sbPricePerUnit->setValue(item->calculatedPrice().value());
}

void AbstractBillItemWizard::displayTemplateData(Template::Ptr item)
{
    if (item == nullptr) {
        return;
    }

    m_materialModel->clear();
    m_materialModel->addAllWithQuantity(item->material());

    ui->sbWorkingHours->setValue(item->workingHours());
    ui->sbPricePerUnit->setValue(item->price().value());
    ui->textEditArticleDesc->setText(item->itemDesc());
    ui->leTemplateName->setText(item->name());
    ui->leTemplateOrg->setText(item->organisation());
    ui->leDesc->setText(item->desc());
    ui->leType->setText(item->type());
    ui->leUnit->setText(item->unit());
    ui->sbTaxRate->setValue(item->taxRate() * 100.0);
}

Template::Ptr AbstractBillItemWizard::toTemplate()
{
    Template::Ptr templ = std::make_shared<Template>();

    templ->setId(m_id);
    templ->setName(ui->leTemplateName->text());
    templ->setOrganisation(ui->leTemplateOrg->text());
    templ->setItemDesc(ui->textEditArticleDesc->toPlainText());
    templ->setUnit(ui->leUnit->text());
    templ->setPrice(Decimal::fromValue(ui->sbPricePerUnit->value()));
    templ->setWorkingHours(ui->sbWorkingHours->value());
    templ->setMaterial(m_materialModel->itemsWithQuantity());
    templ->setDesc(ui->leDesc->text());
    templ->setType(ui->leType->text());
    templ->setTaxRate(ui->sbTaxRate->value() / 100.0);

    return templ;
}

BillItem::Ptr AbstractBillItemWizard::toBillItem()
{
    BillItem::Ptr item = std::make_shared<BillItem>();

    QSettings settings;

    item->setId(m_id);
    item->setDescription(ui->textEditArticleDesc->toPlainText());
    item->setMaterialNetCost(m_materialNetCost);
    item->setMaterialCost(m_materialCost);
    item->setPrice(Decimal::fromValue(ui->sbPricePerUnit->value()));
    item->setQuantity(ui->sbQuantity->value());
    item->setUnit(ui->leUnit->text());
    item->setWorkingHours(ui->sbWorkingHours->value());
    item->setMaterial(m_materialModel->itemsWithQuantity());

    item->setWagePerHour(Decimal::fromValue(settings.value("financial/wage").toDouble()));
    item->setMaterialOverhead(settings.value("financial/materialOverhead").toDouble());
    item->setFactoryOverhead(settings.value("financial/factoryOverhead").toDouble());
    item->setProfit(settings.value("financial/profit").toDouble());
    item->setCashback(settings.value("financial/cashback").toDouble());
    item->setTaxRate(ui->sbTaxRate->value() / 100.0);

    return item;
}
