#ifndef TEMPLATEWIZARD_H
#define TEMPLATEWIZARD_H

#include <QWizard>
#include <QSettings>

#include "domain/billitem.h"

#include "ui/wizards/abstractbillitemwizard.h"

class TemplateWizard : public AbstractBillItemWizard
{
    Q_OBJECT
public:
    TemplateWizard(QWidget *parent, MaterialService::Ptr materialService, TemplateService::Ptr templateService);

    void prepareForCreate() override;
    void prepareForUpdate(Template::Ptr item);

signals:
    void templateUpdated(Template::Ptr);

private:
    bool onUpdate() override;
    bool onCreate() override;
};

#endif // TEMPLATEWIZARD_H
