#ifndef DBCUSTOMERDAO_H
#define DBCUSTOMERDAO_H

#include <memory>
#include <QtSql>

#include "logging.h"

#include "domain/customer.h"
#include "persistence/validation/validator.h"
#include "persistence/customerdao.h"

class DBCustomerDAO : public CustomerDAO
{
public:
    DBCustomerDAO(QSqlDatabase database, Validator<Customer::Ptr>::Ptr validator);

    Customer::Ptr get(int id) override;
    QList<Customer::Ptr> getAll() override;
    void create(Customer::Ptr item) override;
    void update(Customer::Ptr item) override;
    void remove(Customer::Ptr item) override;

private:
    Customer::Ptr parseCustomer(QSqlRecord record);

private:
    QSqlDatabase m_database;
    Validator<Customer::Ptr>::Ptr m_validator;
};

#endif // DBCUSTOMERDAO_H
