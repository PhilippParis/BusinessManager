#ifndef BILLITEMWIZARD_H
#define BILLITEMWIZARD_H

#include <QWizard>
#include <QTextBlock>
#include <QMessageBox>
#include <QDebug>

#include "domain/billitem.h"

#include "service/billservice.h"
#include "service/productservice.h"
#include "service/templateservice.h"

#include "ui/wizards/abstractbillitemwizard.h"
#include "ui/models/producttablemodel.h"
#include "ui/delegates/spinboxdelegate.h"
#include "ui/dialogs/productselectiondialog.h"

class BillItemWizard : public AbstractBillItemWizard
{
    Q_OBJECT

public:
    explicit BillItemWizard(QWidget *parent, BillService::Ptr billService,
                            ProductService::Ptr productService, TemplateService::Ptr templateService);

    void prepareForUpdate(BillItem::Ptr item);
    BillItem::Ptr getBillItemDomainObject();
    Template::Ptr getTemplateDomainObject();

private:
    bool onUpdate() override;
    bool onCreate() override;

private:
    BillService::Ptr m_billService;
};

#endif // BILLITEMWIZARD_H
