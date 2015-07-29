#ifndef USERSETTINGSWIDGET_H
#define USERSETTINGSWIDGET_H

#include <QWidget>
#include <QFileDialog>

#include "ui/widgets/settingswidget.h"

namespace Ui {
class UserSettingsWidget;
}

class UserSettingsWidget : public QWidget, public SettingsWidget
{
    Q_OBJECT

public:
    explicit UserSettingsWidget(QWidget *parent = 0);
    ~UserSettingsWidget();

    void loadSettings(QSettings *settings) override;
    void writeSettings(QSettings *settings) override;

private slots:
    void on_btnLogo_clicked();
    void on_btnSignature_clicked();

private:
    Ui::UserSettingsWidget *ui;
    QString m_logoPath;
    QString m_signaturePath;
};

#endif // USERSETTINGSWIDGET_H
