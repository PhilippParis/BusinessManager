#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <memory>
#include <QStringList>

class Envelope
{
public:
    typedef std::shared_ptr<Envelope> Ptr;

    enum Format {
        Small, Medium, DocumentCase
    };

    Envelope();

    QStringList receiverInfo() const;
    void setReceiverInfo(const QStringList &receiverInfo);

    bool withWindow() const;
    void setWithWindow(bool withWindow);

    int orientation() const;
    void setOrientation(int orientation);

    int pageSize() const;
    void setPageSize(int pageSize);

private:
    int m_orientation;
    int m_pageSize;
    QStringList m_receiverInfo;
    bool m_withWindow;

};

#endif // ENVELOPE_H
