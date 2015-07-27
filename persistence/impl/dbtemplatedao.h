#ifndef DBTEMPLATEDAO_H
#define DBTEMPLATEDAO_H

#include <QtSql>

#include "persistence/templatedao.h"
#include "persistence/productdao.h"

class DBTemplateDAO : public TemplateDAO
{
public:
    DBTemplateDAO(QSqlDatabase database, Validator<Template::Ptr>::Ptr validator, ProductDAO::Ptr productDAO);

    void create(Template::Ptr item) override;
    void update(Template::Ptr item) override;
    void remove(Template::Ptr item) override;
    Template::Ptr get(int id) override;
    QList<Template::Ptr> getAll() override;

private:
    Template::Ptr parseTemplate(QSqlRecord record);
    void updateAssocTable(Template::Ptr item);

private:
    QSqlDatabase m_database;
    Validator<Template::Ptr>::Ptr m_validator;

    ProductDAO::Ptr m_productDAO;

};

#endif // DBTEMPLATEDAO_H
