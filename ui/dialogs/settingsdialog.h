#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "ui/widgets/usersettingswidget.h"
#include "ui/widgets/documentssettingswidget.h"
#include "ui/widgets/financialsettingswidget.h"
#include "ui/widgets/appsettingswidget.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private slots:
    void accept() override;
    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::SettingsDialog *ui;

    QSettings m_settings;
    UserSettingsWidget *m_userSettingsWidget;
    DocumentsSettingsWidget *m_documentsSettingsWidget;
    FinancialSettingsWidget *m_financialSettingsWidget;
    AppSettingsWidget *m_appSettingsWidget;
};

#endif // SETTINGSDIALOG_H
