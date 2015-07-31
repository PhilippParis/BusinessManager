#include "materialselectiondialog.h"
#include "ui_materialselectiondialog.h"

MaterialSelectionDialog::MaterialSelectionDialog(QWidget *parent, MaterialService::Ptr service) :
    QDialog(parent),
    ui(new Ui::MaterialSelectionDialog),
    m_service(service)
{
    ui->setupUi(this);

    m_materialModel = new MaterialTableModel();
    m_sortFilterProxyModel = new MaterialSortFilterProxyModel();
    m_sortFilterProxyModel->setSourceModel(m_materialModel);

    ui->tblMaterials->setModel(m_sortFilterProxyModel);

    // hide quantity column
    ui->tblMaterials->hideColumn(4);

    m_materialModel->addAll(m_service->getAll());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

MaterialSelectionDialog::~MaterialSelectionDialog()
{
    delete ui;
    delete m_materialModel;
    delete m_sortFilterProxyModel;
}

Material::Ptr MaterialSelectionDialog::selectedMaterial() const
{
    QModelIndex currentIndex = ui->tblMaterials->currentIndex();
    return m_materialModel->get(m_sortFilterProxyModel->mapToSource(currentIndex));
}

double MaterialSelectionDialog::quantity() const
{
    return ui->sbQuantity->value();
}

void MaterialSelectionDialog::on_tblMaterials_clicked(const QModelIndex &index)
{
    QString unit = selectedMaterial()->unit();
    ui->sbQuantity->setSuffix(" " + unit);
}

void MaterialSelectionDialog::on_leFilter_textChanged(const QString &arg1)
{
    m_sortFilterProxyModel->setFilterWildcard(arg1);
}

void MaterialSelectionDialog::on_tblMaterials_activated(const QModelIndex &index)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(index.isValid());
}
