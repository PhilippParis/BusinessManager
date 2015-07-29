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
    ui->sbWage->setValue(settings->value("financial/wage").toDouble());
}

void FinancialSettingsWidget::writeSettings(QSettings *settings)
{
    settings->setValue("financial/wage", ui->sbWage->value());
}
