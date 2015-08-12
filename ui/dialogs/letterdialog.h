#ifndef LETTERDIALOG_H
#define LETTERDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDate>

#include "domain/letter.h"
#include "service/customerservice.h"
#include "service/letterservice.h"

#include "ui/models/customertablemodel.h"
#include "ui/dialogs/customerselectiondialog.h"

namespace Ui {
class LetterDialog;
}

class LetterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LetterDialog(QWidget *parent, LetterService::Ptr letterService, CustomerService::Ptr customerService);
    ~LetterDialog();

    void prepareForCreate(Customer::Ptr customer);
    void prepareForUpdate(Letter::Ptr);
    Letter::Ptr toDomainObject();

signals:
    void print(Letter::Ptr);

protected:
    void accept() override;

private slots:
    void on_sbFontSize_valueChanged(int arg1);
    void on_btnAlignLeft_clicked(bool checked);
    void on_btnAlignCenter_clicked(bool checked);
    void on_btnAlignRight_clicked(bool checked);
    void on_btnBold_clicked(bool checked);
    void on_btnItalic_clicked(bool checked);
    void on_btnPrintPreview_clicked();
    void on_cbFont_currentFontChanged(const QFont &f);
    void on_textEdit_cursorPositionChanged();
    void on_btnRecipient_clicked();

private:
    void setCustomer(Customer::Ptr customer);

private:
    enum OpenMode {
        Create, Update
    };
    OpenMode m_openMode;

    Ui::LetterDialog *ui;
    int m_id = -1;
    QDate m_date;
    Customer::Ptr m_customer;
    CustomerService::Ptr m_customerService;
    LetterService::Ptr m_letterService;
};

#endif // LETTERDIALOG_H
