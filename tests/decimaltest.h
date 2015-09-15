#ifndef DECIMALTEST_H
#define DECIMALTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "decimal.h"

class DecimalTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    void conversionTest_data();
    void conversionTest();

    void additionTest_data();
    void additionTest();

    void subtractionTest_data();
    void subtractionTest();

    void multiplicationTest_data();
    void multiplicationTest();

    void divisionTest_data();
    void divisionTest();

    void longCalculationTest_data();
    void longCalculationTest();

private:
};

#endif // DECIMALTEST_H
