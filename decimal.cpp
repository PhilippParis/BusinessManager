#include "decimal.h"

Decimal::Decimal()
{

}

Decimal Decimal::fromCents(long long cents)
{
    return Decimal((double)cents / 100.0);
}

Decimal Decimal::fromValue(double value)
{
    return Decimal(value);
}

Decimal::Decimal(double value)
{
    m_cents.fromDouble(value);
}

Decimal::Decimal(QDecDouble value)
 : m_cents(value)
{

}

void Decimal::operator =(const Decimal &rhs)
{
    m_cents = rhs.m_cents;
}

void Decimal::operator +=(const Decimal &rhs)
{
    m_cents += rhs.m_cents;
}

void Decimal::operator -=(const Decimal &rhs)
{
    m_cents -= rhs.m_cents;
}

Decimal Decimal::operator +(const Decimal &rhs) const
{
    return Decimal(m_cents + rhs.m_cents);
}

Decimal Decimal::operator -(const Decimal &rhs) const
{
    return Decimal(m_cents - rhs.m_cents);
}

Decimal Decimal::operator *(const double rhs) const
{
    return Decimal(m_cents * rhs);
}

Decimal Decimal::operator *(const int rhs) const
{
    return Decimal(m_cents * rhs);
}

double Decimal::operator /(const Decimal &rhs) const
{
    return (m_cents / rhs.m_cents).toDouble();
}

Decimal Decimal::operator /(const double rhs) const
{
    return Decimal(m_cents / rhs);
}

Decimal Decimal::operator /(const int rhs) const
{
    return Decimal(m_cents / rhs);
}

bool Decimal::operator ==(const Decimal &rhs) const
{
    return m_cents == rhs.m_cents;
}

bool Decimal::operator !=(const Decimal &rhs) const
{
    return m_cents != rhs.m_cents;
}

bool Decimal::operator <(const Decimal &rhs) const
{
    return m_cents < rhs.m_cents;
}

bool Decimal::operator <=(const Decimal &rhs) const
{
    return m_cents <= rhs.m_cents;
}

bool Decimal::operator >(const Decimal &rhs) const
{
    return m_cents > rhs.m_cents;
}

bool Decimal::operator >=(const Decimal &rhs) const
{
    return m_cents >= rhs.m_cents;
}

long long Decimal::cents() const
{
    return (m_cents * 100.0).toDouble();
}

double Decimal::value() const
{
    return m_cents.toDouble();
}

