#ifndef TEMPLATESELECTIONDIALOG_H
#define TEMPLATESELECTIONDIALOG_H

#include <QDialog>
#include <QPushButton>

#include "domain/template.h"
#include "ui/models/templatesortfilterproxymodel.h"
#include "ui/models/templatetablemodel.h"
#include "ui/models/materialtablemodel.h"

#include "service/templateservice.h"

namespace Ui {
class TemplateSelectionDialog;
}

class TemplateSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TemplateSelectionDialog(QWidget *parent, TemplateService::Ptr templateService);
    ~TemplateSelectionDialog();

    Template::Ptr selectedTemplate();

private slots:
    void on_leFilter_textChanged(const QString &arg1);
    void on_tblTemplates_clicked(const QModelIndex &index);

private:
    Ui::TemplateSelectionDialog *ui;
    TemplateTableModel *m_templateModel;
    TemplateSortFilterProxyModel *m_templateSortFilterProxyModel;
    TemplateService::Ptr m_templateService;
};

#endif // TEMPLATESELECTIONDIALOG_H
