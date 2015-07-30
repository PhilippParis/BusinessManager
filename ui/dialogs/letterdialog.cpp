#include "letterdialog.h"
#include "ui_letterdialog.h"

LetterDialog::LetterDialog(QWidget *parent, CustomerService::Ptr customerService) :
    QDialog(parent),
    ui(new Ui::LetterDialog),
    m_customerService(customerService)
{
    ui->setupUi(this);

    m_customerModel = new CustomerTableModel();
    m_customerModel->addAll(m_customerService->getAll());

    ui->cbCustomer->setModel(m_customerModel);
}

LetterDialog::~LetterDialog()
{
    delete ui;
    delete m_customerModel;
}

void LetterDialog::on_cbFont_currentFontChanged(const QFont &f)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();
    format.setFont(f);
    cursor.mergeCharFormat(format);
    ui->textEdit->setFocus();
}

void LetterDialog::on_sbFontSize_valueChanged(int value)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    format.setFontPointSize(value);
    cursor.mergeCharFormat(format);
    ui->textEdit->setFocus();
}

void LetterDialog::on_btnAlignLeft_clicked(bool checked)
{
    if(checked)  {
        ui->btnAlignCenter->setChecked(false);
        ui->btnAlignRight->setChecked(false);
    }

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockformat;
    blockformat.setAlignment(Qt::AlignLeft);
    cursor.mergeBlockFormat(blockformat);
    ui->textEdit->setFocus();
}

void LetterDialog::on_btnAlignCenter_clicked(bool checked)
{
    if(checked)  {
        ui->btnAlignLeft->setChecked(false);
        ui->btnAlignRight->setChecked(false);
    }

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockformat;
    blockformat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(blockformat);
    ui->textEdit->setFocus();
}

void LetterDialog::on_btnAlignRight_clicked(bool checked)
{
    if(checked)  {
        ui->btnAlignLeft->setChecked(false);
        ui->btnAlignCenter->setChecked(false);
    }

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockformat;
    blockformat.setAlignment(Qt::AlignRight);
    cursor.mergeBlockFormat(blockformat);
    ui->textEdit->setFocus();
}

void LetterDialog::on_btnBold_clicked(bool checked)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    format.setFontWeight(checked? QFont::Bold : QFont::Normal);
    cursor.mergeCharFormat(format);//do the text as Bold
    ui->textEdit->setFocus();
}

void LetterDialog::on_btnItalic_clicked(bool checked)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    format.setFontItalic(checked);
    cursor.mergeCharFormat(format);
    ui->textEdit->setFocus();
}

void LetterDialog::on_btnSave_clicked()
{
    QFileDialog dialog(this,  tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("pdf");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("PDF Files (*.pdf)");

    if (dialog.exec()) {
        emit save(toDomainObject(), dialog.selectedFiles().first());
    }
}

void LetterDialog::on_btnPrintPreview_clicked()
{
    emit print(toDomainObject());
}

Customer::Ptr LetterDialog::selectedCustomer()
{
    return m_customerModel->get(m_customerModel->index(ui->cbCustomer->currentIndex(), 0));
}

Letter::Ptr LetterDialog::toDomainObject()
{
    Letter::Ptr letter = std::make_shared<Letter>();
    letter->setTextDoc(ui->textEdit->document()->clone());
    letter->setCustomer(selectedCustomer());
    return letter;
}

void LetterDialog::on_textEdit_cursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat blockFormat = cursor.blockFormat();
    QTextCharFormat charFormat = cursor.charFormat();

    ui->btnAlignLeft->setChecked(blockFormat.alignment() == Qt::AlignLeft);
    ui->btnAlignCenter->setChecked(blockFormat.alignment() == Qt::AlignCenter);
    ui->btnAlignRight->setChecked(blockFormat.alignment() == Qt::AlignRight);
    ui->btnItalic->setChecked(charFormat.fontItalic());
    ui->btnBold->setChecked(charFormat.fontWeight() == QFont::Bold);
}
