#ifndef MATERIALSELECTIONDIALOG_H
#define MATERIALSELECTIONDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>

#include "service/materialservice.h"

#include "ui/models/materialtablemodel.h"
#include "ui/models/materialsortfilterproxymodel.h"

namespace Ui {
class MaterialSelectionDialog;
}

class MaterialSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaterialSelectionDialog(QWidget *parent, MaterialService::Ptr service);
    ~MaterialSelectionDialog();

    Material::Ptr selectedMaterial() const;
    double quantity() const;

private slots:
    void on_tblMaterials_clicked(const QModelIndex &index);
    void on_leFilter_textChanged(const QString &arg1);

private:
    Ui::MaterialSelectionDialog *ui;
    MaterialTableModel *m_materialModel;
    MaterialSortFilterProxyModel *m_sortFilterProxyModel;
    MaterialService::Ptr m_service;
};

#endif // MATERIALSELECTIONDIALOG_H
