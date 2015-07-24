#ifndef BILLITEMWIZARD_H
#define BILLITEMWIZARD_H

#include <QWizard>
#include <QTextBlock>
#include <QMessageBox>

#include "domain/billitem.h"

#include "service/billservice.h"
#include "service/productservice.h"
#include "service/templateservice.h"

namespace Ui {
class BillItemWizard;
}

class BillItemWizard : public QWizard
{
    Q_OBJECT

public:
    explicit BillItemWizard(QWidget *parent, BillService::Ptr billService,
                            ProductService::Ptr productService, TemplateService::Ptr templateService);
    ~BillItemWizard();

    void prepareForCreate();
    void prepareForUpdate(BillItem::Ptr item);

    BillItem::Ptr toDomainObject();

private slots:
    void on_textEditArticleDesc_textChanged();
    void accept() override;

private:
    double materialCosts();

private:
    enum OpenMode {
        Create, Update
    };

    Ui::BillItemWizard *ui;
    int m_id = -1;
    BillService::Ptr m_billService;
    ProductService::Ptr m_productService;
    TemplateService::Ptr m_templateService;
    OpenMode m_openMode;
};

#endif // BILLITEMWIZARD_H
