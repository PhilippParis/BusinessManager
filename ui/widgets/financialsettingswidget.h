#ifndef FINANCIALSETTINGSWIDGET_H
#define FINANCIALSETTINGSWIDGET_H

#include <QWidget>

#include "ui/widgets/settingswidget.h"

namespace Ui {
class FinancialSettingsWidget;
}

class FinancialSettingsWidget : public QWidget, public SettingsWidget
{
    Q_OBJECT

public:
    explicit FinancialSettingsWidget(QWidget *parent = 0);
    ~FinancialSettingsWidget();

    void loadSettings(QSettings *settings) override;
    void writeSettings(QSettings *settings) override;

private:
    Ui::FinancialSettingsWidget *ui;
};

#endif // FINANCIALSETTINGSWIDGET_H
