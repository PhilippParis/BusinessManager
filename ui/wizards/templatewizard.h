#ifndef TEMPLATEWIZARD_H
#define TEMPLATEWIZARD_H

#include "ui/wizards/abstractbillitemwizard.h"

class TemplateWizard : public AbstractBillItemWizard
{
public:
    TemplateWizard(QWidget *parent, ProductService::Ptr productService, TemplateService::Ptr templateService);

    void prepareForCreate() override;
    void prepareForUpdate(Template::Ptr item);
    Template::Ptr toDomainObject();

private:
    bool onUpdate();
    bool onCreate();
};

#endif // TEMPLATEWIZARD_H
