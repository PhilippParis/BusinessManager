#ifndef APPSETTINGSWIDGET_H
#define APPSETTINGSWIDGET_H

#include <QWidget>
#include <QFileDialog>

#include "ui/widgets/settingswidget.h"

namespace Ui {
class AppSettingsWidget;
}

class AppSettingsWidget : public QWidget, public SettingsWidget
{
    Q_OBJECT

public:
    explicit AppSettingsWidget(QWidget *parent = 0);
    ~AppSettingsWidget();

    void loadSettings(QSettings *settings) override;
    void writeSettings(QSettings *settings) override;

private slots:
    void on_btnBillDir_clicked();
    void on_btnOfferDir_clicked();
    void on_btnLetterDir_clicked();

private:
    Ui::AppSettingsWidget *ui;
};

#endif // APPSETTINGSWIDGET_H
