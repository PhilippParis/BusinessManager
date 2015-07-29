#include "documentssettingswidget.h"
#include "ui_documentssettingswidget.h"

DocumentsSettingsWidget::DocumentsSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentsSettingsWidget)
{
    ui->setupUi(this);
}

DocumentsSettingsWidget::~DocumentsSettingsWidget()
{
    delete ui;
}

void DocumentsSettingsWidget::loadSettings(QSettings *settings)
{
    ui->leBillText->setText(settings->value("docs/billText").toString());
    ui->leOfferText->setText(settings->value("docs/offerText").toString());
    ui->textEditFooter->setText(settings->value("docs/footer").toString());
    ui->leDateFormat->setText(settings->value("docs/date_format").toString());

    m_color = settings->value("docs/color").value<QColor>();

    ui->lwPrint->item(LOGO)->setCheckState(settings->value("docs/show_logo").toBool() ? Qt::Checked : Qt::Unchecked);
    ui->lwPrint->item(SENDER)->setCheckState(settings->value("docs/show_sender").toBool() ? Qt::Checked : Qt::Unchecked);
    ui->lwPrint->item(BEAM)->setCheckState(settings->value("docs/show_beam").toBool() ? Qt::Checked : Qt::Unchecked);
    ui->lwPrint->item(FOOTER)->setCheckState(settings->value("docs/show_footer").toBool() ? Qt::Checked : Qt::Unchecked);
    ui->lwPrint->item(SIGNATURE)->setCheckState(settings->value("docs/show_signature").toBool() ? Qt::Checked : Qt::Unchecked);
}

void DocumentsSettingsWidget::writeSettings(QSettings *settings)
{
    settings->setValue("docs/billText", ui->leBillText->text());
    settings->setValue("docs/offerText", ui->leOfferText->text());
    settings->setValue("docs/footer", ui->textEditFooter->toPlainText());
    settings->setValue("docs/date_format", ui->leDateFormat->text());

    settings->setValue("docs/color", m_color);

    settings->setValue("docs/show_logo", ui->lwPrint->item(LOGO)->checkState() == Qt::Checked);
    settings->setValue("docs/show_sender", ui->lwPrint->item(SENDER)->checkState() == Qt::Checked);
    settings->setValue("docs/show_beam", ui->lwPrint->item(BEAM)->checkState() == Qt::Checked);
    settings->setValue("docs/show_footer", ui->lwPrint->item(FOOTER)->checkState() == Qt::Checked);
    settings->setValue("docs/show_signature", ui->lwPrint->item(SIGNATURE)->checkState() == Qt::Checked);
}

void DocumentsSettingsWidget::on_btnColor_clicked()
{
    m_color = QColorDialog::getColor(m_color, this);
}
