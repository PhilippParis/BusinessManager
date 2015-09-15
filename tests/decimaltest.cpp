#include "decimaltest.h"


void DecimalTest::initTestCase()
{

}

void DecimalTest::conversionTest_data()
{
    QTest::addColumn<double>("value");
    QTest::addColumn<int>("cents");

    QTest::newRow("0.1") << 0.01 << 1;
    QTest::newRow("0.5") << 0.05 << 5;
    QTest::newRow("0.10") << 0.10 << 10;
    QTest::newRow("0.20") << 0.20 << 20;
    QTest::newRow("0.30") << 0.30 << 30;
    QTest::newRow("0.40") << 0.40 << 40;
    QTest::newRow("0.50") << 0.50 << 50;
    QTest::newRow("0.60") << 0.60 << 60;
    QTest::newRow("0.70") << 0.70 << 70;
    QTest::newRow("0.80") << 0.80 << 80;
    QTest::newRow("0.90") << 0.90 << 90;
    QTest::newRow("1.00") << 1.00 << 100;
    QTest::newRow("1.05") << 1.05 << 105;
    QTest::newRow("1.10") << 1.10 << 110;
    QTest::newRow("1.98") << 1.98 << 198;
    QTest::newRow("1.99") << 1.99 << 199;
    QTest::newRow("2.80") << 2.80 << 280;
    QTest::newRow("99999.99") << 99999.99 << 9999999;
}

void DecimalTest::conversionTest()
{
    QFETCH(double, value);
    QFETCH(int, cents);

    Decimal decimal1 = Decimal::fromValue(value);
    Decimal decimal2 = Decimal::fromCents(cents);

    QCOMPARE(decimal1.cents(), cents);
    QCOMPARE(decimal1.value(), value);

    QCOMPARE(decimal2.value(), value);
    QCOMPARE(decimal2.cents(), cents);

    QCOMPARE(decimal1, decimal2);
}

void DecimalTest::additionTest_data()
{
    QTest::addColumn<double>("op1_value");
    QTest::addColumn<double>("op2_value");
    QTest::addColumn<int>("op3_cents");
    QTest::addColumn<int>("op4_cents");

    QTest::addColumn<double>("result_value");
    QTest::addColumn<int>("result_cents");

    QTest::newRow("row1") << 2.80 << 3.99 << 109 << 304 << 10.92 << 1092;
    QTest::newRow("row2") << 0.00 << 999999.99 << 0 << 1 << 1000000.00 << 100000000;
    QTest::newRow("row3") << 2.80 << 2.80 << 280 << 280 << 11.20 << 1120;
    QTest::newRow("row4") << 0.01 << 0.01 << 1 << 1 << 0.04 << 4;
    QTest::newRow("row5") << 123123.01 << 999999.12 << 523 << 100000 << 1124127.36 << 112412736;
    QTest::newRow("row6") << 0.15 << 0.16 << 1 << 100 << 1.32 << 132;
}

void DecimalTest::additionTest()
{
    QFETCH(double, op1_value);
    QFETCH(double, op2_value);
    QFETCH(int, op3_cents);
    QFETCH(int, op4_cents);
    QFETCH(double, result_value);
    QFETCH(int, result_cents);

    Decimal op1 = Decimal::fromValue(op1_value);
    Decimal op2 = Decimal::fromValue(op2_value);
    Decimal op3 = Decimal::fromCents(op3_cents);
    Decimal op4 = Decimal::fromCents(op4_cents);

    Decimal result = op1 + op2 + op3 + op4;

    QCOMPARE(result.value(), result_value);
    QCOMPARE(result.cents(), result_cents);
}

void DecimalTest::subtractionTest_data()
{
    QTest::addColumn<double>("op1_value");
    QTest::addColumn<double>("op2_value");

    QTest::addColumn<double>("result_value");
    QTest::addColumn<int>("result_cents");

    QTest::newRow("row1") << 2.80 << 2.80 << 0.0 << 0;
    QTest::newRow("row2") << 1.10 << 0.10 << 1.0 << 100;
    QTest::newRow("row3") << 99999.99 << 0.01 << 99999.98 << 9999998;
    QTest::newRow("row4") << 999999.99 << 111111.11 << 888888.88 << 88888888;
    QTest::newRow("row5") << 100.99 << 101.0 << -0.01 << -1;
    QTest::newRow("row6") << 5.79 << 0.39 << 5.40 << 540;

}

void DecimalTest::subtractionTest()
{
    QFETCH(double, op1_value);
    QFETCH(double, op2_value);
    QFETCH(double, result_value);
    QFETCH(int, result_cents);

    Decimal op1 = Decimal::fromValue(op1_value);
    Decimal op2 = Decimal::fromValue(op2_value);

    Decimal result = op1 - op2;

    QCOMPARE(result.value(), result_value);
    QCOMPARE(result.cents(), result_cents);
}

void DecimalTest::multiplicationTest_data()
{
    QTest::addColumn<double>("op1_value");
    QTest::addColumn<double>("op2");
    QTest::addColumn<double>("result_value");
    QTest::addColumn<int>("result_cents");

    QTest::newRow("row1") << 2.80 << 25.0 << 70.0 << 7000;
    QTest::newRow("row2") << 9999.99 << 0.1723 << 1723.00 << 172300;
    QTest::newRow("row3") << 500.0 << 0.2 << 100.0 << 10000;
    QTest::newRow("row4") << 123.01 << 100.0 << 12301.0 << 1230100;
    QTest::newRow("row5") << 99.99 << 0.05 << 5.0 << 500;
}

void DecimalTest::multiplicationTest()
{
    QFETCH(double, op1_value);
    QFETCH(double, op2);
    QFETCH(double, result_value);
    QFETCH(int, result_cents);

    Decimal op1 = Decimal::fromValue(op1_value);
    Decimal result = op1 * op2;

    QCOMPARE(result.value(), result_value);
    QCOMPARE(result.cents(), result_cents);
}

void DecimalTest::divisionTest_data()
{
    QTest::addColumn<double>("op1_value");
    QTest::addColumn<double>("op2");
    QTest::addColumn<double>("result_value");
    QTest::addColumn<int>("result_cents");

    QTest::newRow("row1") << 2.80 << 0.04 << 70.0 << 7000;
    QTest::newRow("row2") << 9999.99 << 2.0 << 5000.00 << 500000;
    QTest::newRow("row3") << 500.0 << 1.0 << 500.0 << 50000;
    QTest::newRow("row4") << 123.01 << 100.0 << 1.23 << 123;
    QTest::newRow("row5") << 99.99 << 0.05 << 1999.8 << 199980;
}

void DecimalTest::divisionTest()
{
    QFETCH(double, op1_value);
    QFETCH(double, op2);
    QFETCH(double, result_value);
    QFETCH(int, result_cents);

    Decimal op1 = Decimal::fromValue(op1_value);
    Decimal result = op1 / op2;

    QCOMPARE(result.value(), result_value);
    QCOMPARE(result.cents(), result_cents);
}

void DecimalTest::longCalculationTest_data()
{
    QTest::addColumn<double>("op1_value");
    QTest::addColumn<double>("op2_value");
    QTest::addColumn<double>("op3_value");
    QTest::addColumn<int>("op4_cents");
    QTest::addColumn<int>("op5_cents");
    QTest::addColumn<double>("d1");
    QTest::addColumn<double>("d2");
    QTest::addColumn<double>("result_value");
    QTest::addColumn<int>("result_cents");

    QTest::newRow("row1") << 2.80 << 1.99 << 9999.01 << 1 << 299 << 0.5 << 1.2 << 20003.89 << 2000389;
    QTest::newRow("row2") << 5.00 << 6.00 << 7.00 << 122 << 301 << 100.0 << 0.5 << 554.30 << 55430;
    QTest::newRow("row3") << 9999.0 << 100.21 << 30000.99 << 600 << 521 << 0.2 << 0.2 << 150420.13 << 15042013;
}

void DecimalTest::longCalculationTest()
{
    // money
    QFETCH(double, op1_value);
    QFETCH(double, op2_value);
    QFETCH(double, op3_value);
    QFETCH(int, op4_cents);
    QFETCH(int, op5_cents);
    // double values
    QFETCH(double, d1);
    QFETCH(double, d2);
    // result
    QFETCH(double, result_value);
    QFETCH(int, result_cents);

    Decimal dec1 = Decimal::fromValue(op1_value);
    Decimal dec2 = Decimal::fromValue(op2_value);
    Decimal dec3 = Decimal::fromValue(op3_value);
    Decimal dec4 = Decimal::fromCents(op4_cents);
    Decimal dec5 = Decimal::fromCents(op5_cents);

    Decimal result = (dec1 *d1) * d2 + (dec2 * d2) * d1 + dec3 / d1 + dec4 + dec5;

    QCOMPARE(result.value(), result_value);
    QCOMPARE(result.cents(), result_cents);
}
