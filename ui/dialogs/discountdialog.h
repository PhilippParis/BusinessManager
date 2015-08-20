#ifndef DISCOUNTDIALOG_H
#define DISCOUNTDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "persistence/validation/validator.h"
#include "domain/discount.h"

namespace Ui {
class DiscountDialog;
}

class DiscountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DiscountDialog(QWidget *parent, Validator<Discount::Ptr>::Ptr validator);
    ~DiscountDialog();

    void prepareForCreate();
    void prepareForUpdate(Discount::Ptr discount);

    Discount::Ptr toDomainObject();

private slots:
    void accept() override;

private:
    enum OpenMode {
        Create, Update
    };
    OpenMode m_openMode;

    Ui::DiscountDialog *ui;
    int m_id = -1;
    Validator<Discount::Ptr>::Ptr m_validator;
};

#endif // DISCOUNTDIALOG_H
