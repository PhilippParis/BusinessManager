#ifndef OFFERWIDGET_H
#define OFFERWIDGET_H

#include <QWidget>

#include "service/offerservice.h"
#include "ui/models/offersortfilterproxymodel.h"
#include "ui/models/offertablemodel.h"

namespace Ui {
class OfferWidget;
}

class OfferWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OfferWidget(QWidget *parent = 0);
    ~OfferWidget();

    void setOfferModel(OfferTableModel *model);
    void setOfferService(OfferService::Ptr offerService);

signals:
    void create();
    void edit(Offer::Ptr);
    void remove(Offer::Ptr);
    void print(Offer::Ptr);
    void saveToFile(Offer::Ptr);

private slots:
    void on_leFilter_textChanged(const QString &arg1);
    void on_btnEdit_clicked();
    void on_btnPrint_clicked();
    void on_btnDelete_clicked();
    void on_tblOffers_clicked(const QModelIndex &index);
    void on_btnExport_clicked();

private:
    Offer::Ptr selectedOffer();

private:
    Ui::OfferWidget *ui;
    OfferService::Ptr m_offerService;
    OfferSortFilterProxyModel *m_sortFilterProxyModel;
    OfferTableModel *m_model;
};

#endif // OFFERWIDGET_H
