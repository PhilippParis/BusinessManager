#include "materialswidget.h"
#include "ui_materialswidget.h"

MaterialsWidget::MaterialsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaterialsWidget)
{
    ui->setupUi(this);

    m_model = new MaterialTableModel();
    m_sortFilterProxyModel = new MaterialSortFilterProxyModel();

    m_sortFilterProxyModel->setSourceModel(m_model);
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
    MaterialDialog *dialog = new MaterialDialog(this, m_service->validator());
    dialog->prepareForCreate();
    if (dialog->exec() == QDialog::Accepted) {
        Material::Ptr material = dialog->toDomainObject();
        try {
            m_service->add(material);
            m_model->add(material, 0.0);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void MaterialsWidget::on_btnEdit_clicked()
{
    Material::Ptr selected = selectedMaterial();
    if (selected == nullptr) {
        return;
    }

    MaterialDialog *dialog = new MaterialDialog(this, m_service->validator());
    dialog->prepareForUpdate(selected);
    if (dialog->exec() == QDialog::Accepted) {
        Material::Ptr material = dialog->toDomainObject();
        try {
            m_service->update(selected);
            m_model->replace(selected, material);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void MaterialsWidget::on_btnDelete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Material"),
                                    tr("Are you sure you want to delete the selected Material?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Material::Ptr selected = selectedMaterial();
        try {
            m_service->remove(selected);
            m_model->remove(selected);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void MaterialsWidget::on_tblMaterials_clicked(const QModelIndex &index)
{
    ui->btnEdit->setEnabled(index.isValid());
    ui->btnDelete->setEnabled(index.isValid());
}
