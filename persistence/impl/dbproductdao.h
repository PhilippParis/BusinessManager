#ifndef DBPRODUCTDAO_H
#define DBPRODUCTDAO_H

#include <memory>
#include <QtSql>

#include "logging.h"

#include "persistence/validation/validator.h"
#include "persistence/productdao.h"

class DBProductDAO : public ProductDAO
{
public:
    DBProductDAO(QSqlDatabase database, Validator<Product::Ptr>::Ptr validator);

    Product::Ptr get(int id) override;
    QList<Product::Ptr> getAll() override;
    bool create(Product::Ptr item) override;
    bool update(Product::Ptr item) override;
    bool remove(Product::Ptr item) override;

private:
    Product::Ptr parseProduct(QSqlRecord record);

private:
    QSqlDatabase m_database;
    Validator<Product::Ptr>::Ptr m_validator;
};

#endif // DBPRODUCTDAO_H
