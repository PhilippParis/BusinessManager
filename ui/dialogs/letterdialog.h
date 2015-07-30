#ifndef LETTERDIALOG_H
#define LETTERDIALOG_H

#include <QDialog>
#include <QFileDialog>

#include "domain/letter.h"
#include "ui/models/customertablemodel.h"
#include "service/customerservice.h"

namespace Ui {
class LetterDialog;
}

class LetterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LetterDialog(QWidget *parent, CustomerService::Ptr customerService);
    ~LetterDialog();

signals:
    void print(Letter::Ptr);
    void save(Letter::Ptr, QString);

private slots:
    void on_sbFontSize_valueChanged(int arg1);
    void on_btnAlignLeft_clicked(bool checked);
    void on_btnAlignCenter_clicked(bool checked);
    void on_btnAlignRight_clicked(bool checked);
    void on_btnBold_clicked(bool checked);
    void on_btnItalic_clicked(bool checked);
    void on_btnSave_clicked();
    void on_btnPrintPreview_clicked();
    void on_cbFont_currentFontChanged(const QFont &f);
    void on_textEdit_cursorPositionChanged();

private:
    Letter::Ptr toDomainObject();
    Customer::Ptr selectedCustomer();

private:
    Ui::LetterDialog *ui;
    CustomerTableModel *m_customerModel;
    CustomerService::Ptr m_customerService;
};

#endif // LETTERDIALOG_H
