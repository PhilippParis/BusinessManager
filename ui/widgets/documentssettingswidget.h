#ifndef DOCUMENTSSETTINGSWIDGET_H
#define DOCUMENTSSETTINGSWIDGET_H

#include <QWidget>
#include <QColorDialog>

#include "ui/widgets/settingswidget.h"

namespace Ui {
class DocumentsSettingsWidget;
}

class DocumentsSettingsWidget : public QWidget, public SettingsWidget
{
    Q_OBJECT

public:
    explicit DocumentsSettingsWidget(QWidget *parent = 0);
    ~DocumentsSettingsWidget();

    void loadSettings(QSettings *settings) override;
    void writeSettings(QSettings *settings) override;

private slots:
    void on_btnColor_clicked();

private:
    enum Items {
        LOGO, SENDER, BEAM, FOOTER, SIGNATURE
    };

    Ui::DocumentsSettingsWidget *ui;
    QColor m_color;
};

#endif // DOCUMENTSSETTINGSWIDGET_H
