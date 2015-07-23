#ifndef BILLITEMWIZARD_H
#define BILLITEMWIZARD_H

#include <QWizard>
#include <QTextBlock>

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

    void prepareForCreate(Bill::Ptr bill);
    void prepareForUpdate(BillItem::Ptr item);

    BillItem::Ptr toDomainObject();

private slots:
    void on_textEditArticleDesc_textChanged();

private:
    double materialCosts();

private:
    Ui::BillItemWizard *ui;
    int m_id = -1;
    Bill::Ptr m_bill;
    BillService::Ptr m_billService;
    ProductService::Ptr m_productService;
    TemplateService::Ptr m_templateService;
};

#endif // BILLITEMWIZARD_H
