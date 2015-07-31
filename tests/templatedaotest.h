#ifndef TEMPLATEDAOTEST_H
#define TEMPLATEDAOTEST_H

#include <QObject>
#include <QTest>
#include <QString>
#include <QTest>
#include <QMap>

#include "persistence/impl/dbtemplatedao.h"
#include "persistence/impl/dbmaterialdao.h"

#include "persistence/databasesingleton.h"

#include "persistence/validation/impl/templatevalidator.h"
#include "persistence/validation/impl/materialvalidator.h"

class TemplateDAOTest : public QObject
{
    Q_OBJECT
private slots:
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
    MaterialDAO::Ptr m_materialDAO;

    Material::Ptr m_validMaterial;
    Material::Ptr m_invalidMaterial;
    Material::Ptr m_nullMaterial;

};
#endif // TEMPLATEDAOTEST_H
