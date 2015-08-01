#include "financialsettingswidget.h"
#include "ui_financialsettingswidget.h"

FinancialSettingsWidget::FinancialSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FinancialSettingsWidget)
{
    ui->setupUi(this);
}

FinancialSettingsWidget::~FinancialSettingsWidget()
{
    delete ui;
}

void FinancialSettingsWidget::loadSettings(QSettings *settings)
{
    ui->leLegalDomicile->setText(settings->value("financial/legal_domicile").toString());

    ui->sbWage->setValue(settings->value("financial/wage").toDouble());
    ui->sbMaterialOverhead->setValue(settings->value("financial/materialOverhead").toDouble() * 100.0);
    ui->sbFactoryOverhead->setValue(settings->value("financial/factoryOverhead").toDouble() * 100.0);
    ui->sbProfit->setValue(settings->value("financial/profit").toDouble() * 100.0);
    ui->sbCashback->setValue(settings->value("financial/cashback").toDouble() * 100.0);
    ui->sbTax->setValue(settings->value("financial/tax").toDouble() * 100.0);
}

void FinancialSettingsWidget::writeSettings(QSettings *settings)
{
    settings->setValue("financial/legal_domicile", ui->leLegalDomicile->text());

    settings->setValue("financial/wage", ui->sbWage->value());
    settings->setValue("financial/materialOverhead", ui->sbMaterialOverhead->value() / 100.0);
    settings->setValue("financial/factoryOverhead", ui->sbFactoryOverhead->value() / 100.0);
    settings->setValue("financial/profit", ui->sbProfit->value() / 100.0);
    settings->setValue("financial/cashback", ui->sbCashback->value() / 100.0);
    settings->setValue("financial/tax", ui->sbTax->value() / 100.0);
}
