#ifndef ABSTRACTBILLITEMWIZARD_H
#define ABSTRACTBILLITEMWIZARD_H

#include <QWizard>
#include <QTextBlock>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

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

signals:
    void templateAdded(Template::Ptr);

private slots:
    void on_textEditArticleDesc_textChanged();
    void accept();
    void on_btnAddMaterial_clicked();
    void on_btnDeleteMaterial_clicked();
    void on_tblTemplates_activated(const QModelIndex &index);
    double updateMaterialCosts();

private:
    virtual bool onUpdate() = 0;
    virtual bool onCreate() = 0;

    Template::Ptr selectedTemplate();

protected:
    Template::Ptr toTemplate();
    void displayTemplateData(Template::Ptr templ);

protected:
    enum OpenMode {
        Create, Update
    };

    enum Pages {
        MaterialsPage, ItemDetailsPage
    };
    Ui::AbstractBillItemWizard *ui;
    int m_id = -1;
    Decimal m_materialCost;

    MaterialService::Ptr m_materialService;
    TemplateService::Ptr m_templateService;
    OpenMode m_openMode;

    TemplateTableModel *m_templateModel;
    TemplateSortFilterProxyModel *m_templateSortFilterProxyModel;
    MaterialTableModel *m_materialModel;

};

#endif // ABSTRACTBILLITEMWIZARD_H
