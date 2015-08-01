#ifndef BILLITEMWIZARD_H
#define BILLITEMWIZARD_H

#include <QWizard>
#include <QTextBlock>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

#include "domain/billitem.h"

#include "service/billservice.h"
#include "service/materialservice.h"
#include "service/templateservice.h"

#include "ui/wizards/abstractbillitemwizard.h"
#include "ui/models/materialtablemodel.h"
#include "ui/delegates/spinboxdelegate.h"
#include "ui/dialogs/materialselectiondialog.h"

class BillItemWizard : public AbstractBillItemWizard
{
    Q_OBJECT
public:
    explicit BillItemWizard(QWidget *parent, BillService::Ptr billService,
                            MaterialService::Ptr materialService, TemplateService::Ptr templateService);

    void prepareForUpdate(BillItem::Ptr item);
    BillItem::Ptr getBillItemDomainObject();
    Template::Ptr getTemplateDomainObject();

private slots:
    void on_BillItemWizard_currentIdChanged(int id);

private:
    bool onUpdate() override;
    bool onCreate() override;

private:
    BillService::Ptr m_billService;
};

#endif // BILLITEMWIZARD_H
