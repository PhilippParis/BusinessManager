#ifndef DBDISCOUNTDAO_H
#define DBDISCOUNTDAO_H

#include <memory>
#include <QtSql>

#include "logging.h"

#include "persistence/discountdao.h"
#include "persistence/validation/validator.h"

class DBDiscountDAO : public DiscountDAO
{
public:
    DBDiscountDAO(QSqlDatabase database, Validator<Discount::Ptr>::Ptr validator);

    void create(Discount::Ptr item) override;
    void update(Discount::Ptr item) override;
    void remove(Discount::Ptr item) override;

    Discount::Ptr get(int id) override;
    QList<Discount::Ptr> getDiscountsOfBill(int billID) override;

private:
    Discount::Ptr parseDiscount(QSqlRecord record);

private:
    QSqlDatabase m_database;
    Validator<Discount::Ptr>::Ptr m_validator;
};

#endif // DBDISCOUNTDAO_H
