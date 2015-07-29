#ifndef TEMPLATEWIZARD_H
#define TEMPLATEWIZARD_H

#include <QWizard>
#include "ui/wizards/abstractbillitemwizard.h"

class TemplateWizard : public AbstractBillItemWizard
{
    Q_OBJECT
public:
    TemplateWizard(QWidget *parent, ProductService::Ptr productService, TemplateService::Ptr templateService);

    void prepareForCreate() override;
    void prepareForUpdate(Template::Ptr item);
    Template::Ptr toDomainObject();

private:
    bool onUpdate() override;
    bool onCreate() override;
};

#endif // TEMPLATEWIZARD_H
