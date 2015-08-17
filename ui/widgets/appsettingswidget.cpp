#include "appsettingswidget.h"
#include "ui_appsettingswidget.h"

AppSettingsWidget::AppSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppSettingsWidget)
{
    ui->setupUi(this);
}

AppSettingsWidget::~AppSettingsWidget()
{
    delete ui;
}

void AppSettingsWidget::loadSettings(QSettings *settings)
{
    ui->leBillDir->setText(settings->value("app/billDir").toString());
    ui->leOfferDir->setText(settings->value("app/offerDir").toString());
    ui->leLetterDir->setText(settings->value("app/letterDir").toString());
}

void AppSettingsWidget::writeSettings(QSettings *settings)
{
    settings->setValue("app/billDir", ui->leBillDir->text());
    settings->setValue("app/offerDir", ui->leOfferDir->text());
    settings->setValue("app/letterDir", ui->leLetterDir->text());
}

void AppSettingsWidget::on_btnBillDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"), ui->leBillDir->text());
    if (!dir.isEmpty()) {
        ui->leBillDir->setText(dir);
    }
}

void AppSettingsWidget::on_btnOfferDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"), ui->leOfferDir->text());
    if (!dir.isEmpty()) {
        ui->leOfferDir->setText(dir);
    }
}

void AppSettingsWidget::on_btnLetterDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose Directory"), ui->leLetterDir->text());
    if (!dir.isEmpty()) {
        ui->leLetterDir->setText(dir);
    }
}

void AppSettingsWidget::loadLanguages()
{
}
