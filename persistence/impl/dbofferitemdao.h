#ifndef DBOFFERITEMDAO_H
#define DBOFFERITEMDAO_H

#include "persistence/offeritemdao.h"
#include "persistence/impl/dbitemdao.h"

class DBOfferItemDAO : public OfferItemDAO, public DBItemDAO
{
public:
    DBOfferItemDAO(QSqlDatabase db, Validator<BillItem::Ptr>::Ptr validator, MaterialDAO::Ptr materialDAO);

    void create(BillItem::Ptr item) override;
    void update(BillItem::Ptr item) override;
    void remove(BillItem::Ptr item) override;
    BillItem::Ptr get(int id) override;
    QList<BillItem::Ptr> getAll() override;
    QList<BillItem::Ptr> getItemsOfOffer(int offerID) override;
};

#endif // DBOFFERITEMDAO_H
