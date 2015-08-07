#include "materialswidget.h"
#include "ui_materialswidget.h"

MaterialsWidget::MaterialsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialsWidget)
{
    ui->setupUi(this);

    m_sortFilterProxyModel = new MaterialSortFilterProxyModel();

    ui->tblMaterials->setModel(m_sortFilterProxyModel);
    ui->tblMaterials->setSortingEnabled(true);
    ui->tblMaterials->hideColumn(4);

    connect(ui->leFilter, SIGNAL(textChanged(QString)), m_sortFilterProxyModel, SLOT(setFilterWildcard(QString)));
}

MaterialsWidget::~MaterialsWidget()
{
    delete ui;
    delete m_model;
    delete m_sortFilterProxyModel;
}

void MaterialsWidget::setMaterialService(MaterialService::Ptr service)
{
    m_service = service;
    update();
}

void MaterialsWidget::setMaterialModel(MaterialTableModel *model)
{
    m_model = model;
    m_sortFilterProxyModel->setSourceModel(m_model);
}

Material::Ptr MaterialsWidget::selectedMaterial()
{
    QModelIndex index = ui->tblMaterials->currentIndex();
    return m_model->get(m_sortFilterProxyModel->mapToSource(index));
}

void MaterialsWidget::update()
{
    m_model->addAll(m_service->getAll());
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
