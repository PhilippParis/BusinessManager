#ifndef MATERIALDIALOG_H
#define MATERIALDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "domain/material.h"
#include "persistence/validation/validator.h"

namespace Ui {
class MaterialDialog;
}

class MaterialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaterialDialog(QWidget *parent, Validator<Material::Ptr>::Ptr validator);
    ~MaterialDialog();

    void prepareForCreate();
    void prepareForUpdate(Material::Ptr material);

    Material::Ptr toDomainObject();

private slots:
    void accept() override;
    void on_leUnit_textChanged(const QString &arg1);

private:
    enum OpenMode {
        Create, Update
    };
    OpenMode m_openMode;

    int m_id = -1;
    Ui::MaterialDialog *ui;
    Validator<Material::Ptr>::Ptr m_validator;
};

#endif // MATERIALDIALOG_H
