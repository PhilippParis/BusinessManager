#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QSettings>

class SettingsWidget
{
public:
    SettingsWidget();

    virtual void loadSettings(QSettings *settings) = 0;
    virtual void writeSettings(QSettings *settings) = 0;
};

#endif // SETTINGSWIDGET_H
