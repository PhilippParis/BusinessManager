#ifndef LETTERWIDGET_H
#define LETTERWIDGET_H

#include <QWidget>
#include <QPrintPreviewWidget>

#include "service/printservice.h"
#include "ui/models/lettertablemodel.h"
#include "ui/models/lettersortfilterproxymodel.h"

namespace Ui {
class LetterWidget;
}

class LetterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LetterWidget(QWidget *parent = 0);
    ~LetterWidget();
    void setLetterModel(LetterTableModel *model);
    void setPrintService(PrintService::Ptr service);

signals:
    void edit(Letter::Ptr);
    void remove(Letter::Ptr);
    void saveToFile(Letter::Ptr);
    void print(Letter::Ptr);

private slots:
    void on_leFilter_textChanged(const QString &arg1);
    void on_btnEdit_clicked();
    void on_btnExport_clicked();
    void on_btnPrint_clicked();
    void on_btnDelete_clicked();

    void on_tblLetters_clicked(const QModelIndex &index);

private:
    Letter::Ptr selectedLetter();

private:
    Ui::LetterWidget *ui;
    LetterTableModel *m_model;
    LetterSortFilterProxyModel *m_sortFilterProxyModel;
    QPrintPreviewWidget *m_printPreviewWidget;

};

#endif // LETTERWIDGET_H
