#ifndef TEMPLATESWIDGET_H
#define TEMPLATESWIDGET_H

#include <QWidget>

#include "ui/models/templatesortfilterproxymodel.h"
#include "ui/models/templatetablemodel.h"

#include "ui/wizards/templatewizard.h"

namespace Ui {
class TemplatesWidget;
}

class TemplatesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TemplatesWidget(QWidget *parent = 0);
    ~TemplatesWidget();

    void setTemplateService(const TemplateService::Ptr &templateService);
    void setMaterialService(const MaterialService::Ptr &materialService);

private slots:
    void update();
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();

    void on_tblTemplates_clicked(const QModelIndex &index);

private:
    Template::Ptr selectedTemplate();

private:
    Ui::TemplatesWidget *ui;
    TemplateTableModel *m_model;
    TemplateSortFilterProxyModel *m_sortFilterProxyModel;


    MaterialService::Ptr m_materialService;
    TemplateService::Ptr m_templateService;
};

#endif // TEMPLATESWIDGET_H
