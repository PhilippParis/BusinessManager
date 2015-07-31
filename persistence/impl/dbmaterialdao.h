#ifndef DBMATERIALDAO_H
#define DBMATERIALDAO_H

#include <memory>
#include <QtSql>

#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/materialdao.h"

class DBMaterialDAO : public MaterialDAO
{
public:
    DBMaterialDAO(QSqlDatabase database, Validator<Material::Ptr>::Ptr validator);

    Material::Ptr get(int id) override;
    QList<Material::Ptr> getAll() override;
    void create(Material::Ptr item) override;
    void update(Material::Ptr item) override;
    void remove(Material::Ptr item) override;

private:
    Material::Ptr parseMaterial(QSqlRecord record);

private:
    QSqlDatabase m_database;
    Validator<Material::Ptr>::Ptr m_validator;
};

#endif // DBMATERIALDAO_H
