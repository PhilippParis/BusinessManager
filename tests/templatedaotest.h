#ifndef TEMPLATEDAOTEST_H
#define TEMPLATEDAOTEST_H

#include <QObject>
#include <QTest>
#include <QString>
#include <QMap>

#include "persistence/impl/dbtemplatedao.h"
#include "persistence/impl/dbproductdao.h"

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/templatevalidator.h"
#include "persistence/validation/impl/productvalidator.h"

class TemplateDAOTest : public QObject
{
    Q_OBJECT
public:
    void initTestCase();

    void insertTest_data();
    void insertTest();

    void updateTest_data();
    void updateTest();
    void updateWithInvalidIDTest();

    void removeTestWithValidIDShouldPass();
    void removeTestWithInValidIDShouldFail();

    void getAllTest();

private:
    TemplateDAO::Ptr m_templateDAO;
    ProductDAO::Ptr m_productDAO;

    Product::Ptr m_validProduct;
    Product::Ptr m_invalidProduct;
    Product::Ptr m_nullProduct;

};
#endif // TEMPLATEDAOTEST_H
