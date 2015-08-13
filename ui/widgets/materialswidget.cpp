#include "materialswidget.h"
#include "ui_materialswidget.h"

MaterialsWidget::MaterialsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialsWidget)
{
    ui->setupUi(this);

    m_sortFilterProxyModel = new MaterialSortFilterProxyModel();
    m_sortFilterProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tblMaterials->setModel(m_sortFilterProxyModel);
    ui->tblMaterials->setSortingEnabled(true);

    connect(ui->leFilter, SIGNAL(textChanged(QString)), m_sortFilterProxyModel, SLOT(setFilterWildcard(QString)));
}

MaterialsWidget::~MaterialsWidget()
{
    delete ui;
    delete m_sortFilterProxyModel;
}

void MaterialsWidget::setMaterialModel(MaterialTableModel *model)
{
    m_model = model;
    m_sortFilterProxyModel->setSourceModel(m_model);
    ui->tblMaterials->hideColumn(5);
}

Material::Ptr MaterialsWidget::selectedMaterial()
{
    QModelIndex index = ui->tblMaterials->currentIndex();
    return m_model->get(m_sortFilterProxyModel->mapToSource(index));
}

void MaterialsWidget::on_btnAdd_clicked()
{
    emit create();
}

void MaterialsWidget::on_btnEdit_clicked()
{
    emit edit(selectedMaterial());
}

void MaterialsWidget::on_btnDelete_clicked()
{
    emit remove(selectedMaterial());
}

void MaterialsWidget::on_tblMaterials_clicked(const QModelIndex &index)
{
    ui->btnEdit->setEnabled(index.isValid());
    ui->btnDelete->setEnabled(index.isValid());
}
