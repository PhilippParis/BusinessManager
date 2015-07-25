#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <memory>
#include <QString>

class Discount
{
public:
    typedef std::shared_ptr<Discount> Ptr;
    Discount();

    double value() const;
    void setValue(double value);

    QString text() const;
    void setText(const QString &text);

    int id() const;
    void setId(int id);

    QString toString() const;
    bool equals(Discount::Ptr item) const;

private:
    int m_id = -1;
    QString m_text = "";
    double m_value = -1;
};

#endif // DISCOUNT_H
