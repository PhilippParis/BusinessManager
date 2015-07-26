#ifndef PRODUCTDIALOG_H
#define PRODUCTDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "domain/product.h"
#include "persistence/validation/validator.h"

namespace Ui {
class ProductDialog;
}

class ProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductDialog(QWidget *parent, Validator<Product::Ptr>::Ptr validator);
    ~ProductDialog();

    void prepareForCreate();
    void prepareForUpdate(Product::Ptr product);

    Product::Ptr toDomainObject();

private slots:
    void accept() override;

    void on_leUnit_textChanged(const QString &arg1);

private:
    enum OpenMode {
        Create, Update
    };
    OpenMode m_openMode;

    int m_id = -1;
    Ui::ProductDialog *ui;
    Validator<Product::Ptr>::Ptr m_validator;
};

#endif // PRODUCTDIALOG_H
