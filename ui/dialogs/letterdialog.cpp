#include "letterdialog.h"
#include "ui_letterdialog.h"

LetterDialog::LetterDialog(QWidget *parent, LetterService::Ptr letterService, CustomerService::Ptr customerService) :
    QDialog(parent),
    ui(new Ui::LetterDialog),
    m_letterService(letterService),
    m_customerService(customerService)
{
    ui->setupUi(this);
}

LetterDialog::~LetterDialog()
{
    delete ui;
}

void LetterDialog::prepareForCreate(Customer::Ptr customer)
{
    m_openMode = Create;
    setCustomer(customer);
    m_date = QDate::currentDate();
    ui->textEdit->clear();
}

void LetterDialog::prepareForUpdate(Letter::Ptr letter)
{
    m_openMode = Update;
    m_id = letter->id();
    m_date = letter->date();
    ui->textEdit->setDocument(letter->textDoc());
    setCustomer(letter->customer());
}

void LetterDialog::accept()
{
    Letter::Ptr letter = toDomainObject();
    try {
        if(m_openMode == Create) {
            m_letterService->validator()->validateForCreate(letter);
        } else {
            m_letterService->validator()->validateForUpdate(letter);
        }
        QDialog::accept();
    } catch (ValidationException *e) {
        QMessageBox::warning(this, "Invalid Data", e->what());
        delete e;
    }
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

void LetterDialog::on_btnPrintPreview_clicked()
{
    emit print(toDomainObject());
}

Letter::Ptr LetterDialog::toDomainObject()
{
    Letter::Ptr letter = std::make_shared<Letter>();
    letter->setTextDoc(ui->textEdit->document()->clone());
    letter->setCustomer(m_customer);
    letter->setDate(m_date);
    letter->setId(m_id);
    return letter;
}

void LetterDialog::setCustomer(Customer::Ptr customer)
{
    m_customer = customer;

    QString text;
    if(m_customer->organisation().isEmpty()) {
        text = m_customer->fullName();
    } else {
        text = m_customer->organisation() + "\n" + m_customer->fullName();
    }

    ui->btnRecipient->setText(text);
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

void LetterDialog::on_btnRecipient_clicked()
{
    CustomerSelectionDialog *dialog = new CustomerSelectionDialog(this, m_customerService);
    if (dialog->exec() == QDialog::Accepted) {
        setCustomer(dialog->selectedCustomer());
    }

    delete dialog;
}
