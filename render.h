#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <QQuickImageProvider>
#include <QPixmapCache>

class Render : public QObject, public QQuickImageProvider
{
    Q_OBJECT
    Q_PROPERTY(unsigned rule WRITE setRule READ rule)
    Q_PROPERTY(unsigned random MEMBER m_random)

public:
    Render();
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize& requestedSize) override;
    inline unsigned rule() const { return m_rule; }

public slots:
    void setRule(unsigned rule);

protected:
    unsigned m_rule;
    bool m_random = false;
    QPixmapCache m_pixCache;
    std::vector<std::pair<size_t, std::vector<bool>>> m_cache;
    const size_t m_w, m_h, m_computed_w;
};

#endif // RENDER_H
