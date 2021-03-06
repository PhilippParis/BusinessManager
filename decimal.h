#ifndef DECIMAL_H
#define DECIMAL_H

#include "qdecimal/QDecDouble.hh"

class Decimal
{

public:
    Decimal();
    static Decimal fromCents(long long cents);
    static Decimal fromValue(double value);

    void operator =(const Decimal& rhs);
    void operator +=(const Decimal& rhs);
    void operator -=(const Decimal& rhs);
    Decimal operator +(const Decimal& rhs) const;
    Decimal operator -(const Decimal& rhs) const;
    Decimal operator *(const Decimal& rhs) const;
    Decimal operator *(const double rhs) const;
    Decimal operator *(const int rhs) const;
    double operator /(const Decimal& rhs) const;
    Decimal operator /(const int rhs) const;
    Decimal operator /(const double rhs) const;
    bool operator ==(const Decimal& rhs) const;
    bool operator !=(const Decimal& rhs) const;
    bool operator <(const Decimal& rhs) const;
    bool operator <=(const Decimal& rhs) const;
    bool operator >(const Decimal& rhs) const;
    bool operator >=(const Decimal& rhs) const;

    long long cents() const;
    double value() const;

private:
    Decimal(double value);
    Decimal(QDecDouble value);

private:
    QDecDouble m_cents = 0.0;
};

#endif // DECIMAL_H
