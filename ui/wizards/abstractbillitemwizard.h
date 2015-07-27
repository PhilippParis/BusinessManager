#ifndef ABSTRACTBILLITEMWIZARD_H
#define ABSTRACTBILLITEMWIZARD_H

#include <QWizard>
#include <QTextBlock>
#include <QMessageBox>
#include <QDebug>

#include "service/productservice.h"
#include "service/templateservice.h"

#include "ui/models/producttablemodel.h"
#include "ui/models/templatesortfilterproxymodel.h"
#include "ui/models/templatetablemodel.h"
#include "ui/delegates/spinboxdelegate.h"
#include "ui/dialogs/productselectiondialog.h"

namespace Ui {
class AbstractBillItemWizard;
}

class AbstractBillItemWizard : public QWizard
{
    Q_OBJECT
public:
    AbstractBillItemWizard(QWidget *parent, ProductService::Ptr productService, TemplateService::Ptr templateService);
    ~AbstractBillItemWizard();

    virtual void prepareForCreate();

private slots:
    virtual void on_textEditArticleDesc_textChanged();
    virtual void accept();
    virtual void on_btnAddMaterial_clicked();
    virtual void on_btnDeleteMaterial_clicked();
    virtual void on_AbstractBillItemWizard_currentIdChanged(int id);

    void on_tblTemplates_activated(const QModelIndex &index);

private:
    virtual bool onUpdate() = 0;
    virtual bool onCreate() = 0;
    Template::Ptr selectedTemplate();

protected:
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

    ProductService::Ptr m_productService;
    TemplateService::Ptr m_templateService;
    OpenMode m_openMode;

    TemplateTableModel *m_templateModel;
    TemplateSortFilterProxyModel *m_templateSortFilterProxyModel;
    ProductTableModel *m_productModel;

};

#endif // ABSTRACTBILLITEMWIZARD_H
