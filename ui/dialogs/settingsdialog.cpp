#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    m_userSettingsWidget = new UserSettingsWidget(this);
    m_documentsSettingsWidget = new DocumentsSettingsWidget(this);
    m_financialSettingsWidget = new FinancialSettingsWidget(this);
    m_appSettingsWidget = new AppSettingsWidget(this);

    m_userSettingsWidget->loadSettings(&m_settings);
    m_documentsSettingsWidget->loadSettings(&m_settings);
    m_financialSettingsWidget->loadSettings(&m_settings);
    m_appSettingsWidget->loadSettings(&m_settings);

    ui->stackedWidget->addWidget(m_userSettingsWidget);
    ui->stackedWidget->addWidget(m_documentsSettingsWidget);
    ui->stackedWidget->addWidget(m_financialSettingsWidget);
    ui->stackedWidget->addWidget(m_appSettingsWidget);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::accept()
{
    m_userSettingsWidget->writeSettings(&m_settings);
    m_documentsSettingsWidget->writeSettings(&m_settings);
    m_financialSettingsWidget->writeSettings(&m_settings);
    m_appSettingsWidget->writeSettings(&m_settings);

    QDialog::accept();
}

void SettingsDialog::on_listWidget_currentRowChanged(int currentRow)
{
    ui->stackedWidget->setCurrentIndex(currentRow);
}
