#include "usersettingswidget.h"
#include "ui_usersettingswidget.h"

UserSettingsWidget::UserSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSettingsWidget)
{
    ui->setupUi(this);
}

UserSettingsWidget::~UserSettingsWidget()
{
    delete ui;
}

void UserSettingsWidget::loadSettings(QSettings *settings)
{
    ui->leStreet->setText(settings->value("user/street").toString());
    ui->leCity->setText(settings->value("user/city").toString());
    ui->leTel->setText(settings->value("user/phone").toString());
    ui->leWebsite->setText(settings->value("user/website").toString());
    ui->leMail->setText(settings->value("user/mail").toString());

    ui->leBIC->setText(settings->value("user/bic").toString());
    ui->leIBAN->setText(settings->value("user/iban").toString());

    m_logoPath = settings->value("user/logo").toString();
    if (!m_logoPath.isEmpty()) {
        ui->lblLogo->setPixmap(QPixmap(m_logoPath));
    }

    m_signaturePath = settings->value("user/signature").toString();
    if (!m_signaturePath.isEmpty()) {
        ui->lblSignature->setPixmap(QPixmap(m_signaturePath));
    }
}

void UserSettingsWidget::writeSettings(QSettings *settings)
{
    settings->setValue("user/street", ui->leStreet->text());
    settings->setValue("user/city", ui->leCity->text());
    settings->setValue("user/phone", ui->leTel->text());
    settings->setValue("user/website", ui->leWebsite->text());
    settings->setValue("user/mail", ui->leMail->text());
    settings->setValue("user/bic", ui->leBIC->text());
    settings->setValue("user/iban", ui->leIBAN->text());

    settings->setValue("user/logo", m_logoPath);
    settings->setValue("user/signature", m_signaturePath);
}

void UserSettingsWidget::on_btnLogo_clicked()
{
    m_logoPath = QFileDialog::getOpenFileName(this,"choose logo", m_logoPath, "*.png");
}

void UserSettingsWidget::on_btnSignature_clicked()
{
    m_signaturePath = QFileDialog::getOpenFileName(this,"choose signature", m_signaturePath, "*.png");
}
