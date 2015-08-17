#ifndef MATERIALDIALOG_H
#define MATERIALDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include "domain/material.h"
#include "service/materialservice.h"

namespace Ui {
class MaterialDialog;
}

class MaterialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaterialDialog(QWidget *parent, MaterialService::Ptr service);
    ~MaterialDialog();

    void prepareForCreate();
    void prepareForUpdate(Material::Ptr material);

signals:
    void materialAdded(Material::Ptr);
    void materialUpdated(Material::Ptr);

private slots:
    void accept() override;
    void on_leUnit_textChanged(const QString &arg1);

private:
    Material::Ptr toDomainObject();

private:
    enum OpenMode {
        Create, Update
    };
    OpenMode m_openMode;

    int m_id = -1;
    Ui::MaterialDialog *ui;
    MaterialService::Ptr m_service;
};

#endif // MATERIALDIALOG_H
