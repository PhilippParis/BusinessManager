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

    /**
     * @return returns if the envelop has a window
     */
    bool withWindow() const;

    /**
     * @brief sets if the envelope has a window
     * @param withWindow has window
     */
    void setWithWindow(bool withWindow);

    /**
     * @return returns the orientation of the envelope
     * @see QPrinter::Orientation
     */
    int orientation() const;

    /**
     * @brief sets the orientation of the envelope
     * @see QPrinter::Orientation
     * @param orientation orientation
     */
    void setOrientation(int orientation);

    /**
     * @return returns the pageSize
     * @see QPagedPaintDevice::PageSize
     */
    int pageSize() const;

    /**
     * @brief sets the page size
     * @see QPagedPaintDevice::PageSize
     * @param pageSize page size
     */
    void setPageSize(int pageSize);

    /**
     * @return returns the receiver name and address
     */
    QStringList receiverInfo() const;

    /**
     * @brief sets the receiver name and address
     * @param receiverInfo receiver name and address
     */
    void setReceiverInfo(const QStringList &receiverInfo);

private:
    int m_orientation;
    int m_pageSize;
    QStringList m_receiverInfo;
    bool m_withWindow;

};

#endif // ENVELOPE_H
