#include "abstractbillitemwizard.h"
#include "ui_abstractbillitemwizard.h"

AbstractBillItemWizard::AbstractBillItemWizard(QWidget *parent, ProductService::Ptr productService, TemplateService::Ptr templateService)
    : QWizard(parent),
      ui(new Ui::AbstractBillItemWizard),
      m_productService(productService),
      m_templateService(templateService)
{
    ui->setupUi(this);
    m_productModel = new ProductTableModel();
    SpinBoxDelegate* delegate = new SpinBoxDelegate(ui->tblMaterial);
    ui->tblMaterial->setModel(m_productModel);
    ui->tblMaterial->setItemDelegateForColumn(4, delegate);

    m_templateModel = new TemplateTableModel();
    m_templateSortFilterProxyModel = new TemplateSortFilterProxyModel();
    m_templateSortFilterProxyModel->setSourceModel(m_templateModel);
    ui->tblTemplates->setModel(m_templateSortFilterProxyModel);

    m_templateModel->addAll(templateService->getAll());
}

AbstractBillItemWizard::~AbstractBillItemWizard()
{
    delete ui;
    delete m_productModel;
}

void AbstractBillItemWizard::prepareForCreate()
{
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
    ProductSelectionDialog *dialog = new ProductSelectionDialog(this, m_productService);
    if(dialog->exec() == QDialog::Accepted) {
        m_productModel->add(dialog->selectedProduct(), dialog->quantity());
    }
}

void AbstractBillItemWizard::on_btnDeleteMaterial_clicked()
{
    m_productModel->remove(m_productModel->get(ui->tblMaterial->currentIndex()));
}

void AbstractBillItemWizard::on_AbstractBillItemWizard_currentIdChanged(int id)
{
    if (id == ItemDetailsPage) {
        ui->lblCostPerArticle->setText(QString::number(totalCostsPerUnit(), 'f', 2) + QString::fromUtf8("€"));
    }
}

double AbstractBillItemWizard::materialCosts()
{
    QMap<Product::Ptr, double> items = m_productModel->itemsWithQuantity();
    double materialCosts = 0.0;

    QMap<Product::Ptr, double>::iterator it;
    for(it = items.begin(); it != items.end(); ++it) {
        materialCosts += it.key()->costPerUnit() * it.value();
    }

    return materialCosts;
}

double AbstractBillItemWizard::totalCostsPerUnit()
{
    return materialCosts() + ui->sbWorkingHours->value() * ui->sbWage->value();
}

void AbstractBillItemWizard::on_tblTemplates_activated(const QModelIndex &index)
{
    m_productModel->clear();
    Template::Ptr templ = selectedTemplate();
    m_productModel->addAllWithQuantity(templ->material());
}

Template::Ptr AbstractBillItemWizard::selectedTemplate()
{
    QModelIndex index = ui->tblTemplates->currentIndex();
    return m_templateModel->get(m_templateSortFilterProxyModel->mapToSource(index));
}
