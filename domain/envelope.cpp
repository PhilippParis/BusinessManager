#include "envelope.h"

Envelope::Envelope()
{

}

QStringList Envelope::receiverInfo() const
{
    return m_receiverInfo;
}

void Envelope::setReceiverInfo(const QStringList &receiverInfo)
{
    m_receiverInfo = receiverInfo;
}

bool Envelope::withWindow() const
{
    return m_withWindow;
}

void Envelope::setWithWindow(bool withWindow)
{
    m_withWindow = withWindow;
}

int Envelope::orientation() const
{
    return m_orientation;
}

void Envelope::setOrientation(int orientation)
{
    m_orientation = orientation;
}
int Envelope::pageSize() const
{
    return m_pageSize;
}

void Envelope::setPageSize(int pageSize)
{
    m_pageSize = pageSize;
}







