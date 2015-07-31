#ifndef ABSTRACTBILLITEMWIZARD_H
#define ABSTRACTBILLITEMWIZARD_H

#include <QWizard>
#include <QTextBlock>
#include <QMessageBox>
#include <QDebug>

#include "service/materialservice.h"
#include "service/templateservice.h"

#include "ui/models/materialtablemodel.h"
#include "ui/models/templatesortfilterproxymodel.h"
#include "ui/models/templatetablemodel.h"
#include "ui/delegates/spinboxdelegate.h"
#include "ui/dialogs/materialselectiondialog.h"

namespace Ui {
class AbstractBillItemWizard;
}

class AbstractBillItemWizard : public QWizard
{
    Q_OBJECT
public:
    AbstractBillItemWizard(QWidget *parent, MaterialService::Ptr materialService, TemplateService::Ptr templateService);
    ~AbstractBillItemWizard();

    virtual void prepareForCreate();
    void setWagePerHour(double wagePerHour);

private slots:
    virtual void on_textEditArticleDesc_textChanged();
    virtual void accept();
    virtual void on_btnAddMaterial_clicked();
    virtual void on_btnDeleteMaterial_clicked();
    virtual void on_AbstractBillItemWizard_currentIdChanged(int id);
    virtual void on_tblTemplates_activated(const QModelIndex &index);

private:
    virtual bool onUpdate() = 0;
    virtual bool onCreate() = 0;

    Template::Ptr selectedTemplate();
    void displayTemplateData(Template::Ptr templ);

protected:
    Template::Ptr toTemplate();
    double materialCosts();
    double totalCostsPerUnit();

protected:
    enum OpenMode {
        Create, Update
    };

    enum Pages {
        MaterialsPage, ItemDetailsPage
    };
    Ui::AbstractBillItemWizard *ui;
    int m_id = -1;
    double m_wagePerHour = 0.0;

    MaterialService::Ptr m_materialService;
    TemplateService::Ptr m_templateService;
    OpenMode m_openMode;

    TemplateTableModel *m_templateModel;
    TemplateSortFilterProxyModel *m_templateSortFilterProxyModel;
    MaterialTableModel *m_materialModel;

};

#endif // ABSTRACTBILLITEMWIZARD_H
