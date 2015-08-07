#ifndef MATERIALSWIDGET_H
#define MATERIALSWIDGET_H

#include <QWidget>

#include "service/materialservice.h"

#include "ui/models/materialtablemodel.h"
#include "ui/models/materialsortfilterproxymodel.h"

#include "ui/dialogs/materialdialog.h"

namespace Ui {
class MaterialsWidget;
}

class MaterialsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialsWidget(QWidget *parent = 0);
    ~MaterialsWidget();

    void setMaterialService(MaterialService::Ptr service);
    void setMaterialModel(MaterialTableModel *model);
    Material::Ptr selectedMaterial();

signals:
    void create();
    void edit(Material::Ptr);
    void remove(Material::Ptr);

private slots:
    void update();
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
    void on_tblMaterials_clicked(const QModelIndex &index);

private:
    Ui::MaterialsWidget *ui;

    MaterialService::Ptr m_service;
    MaterialTableModel *m_model;
    MaterialSortFilterProxyModel *m_sortFilterProxyModel;
};

#endif // MATERIALSWIDGET_H
