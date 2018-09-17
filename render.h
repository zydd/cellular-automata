#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <QQuickImageProvider>
#include <QPixmapCache>

class Render : public QQuickImageProvider
{
public:
    Render(unsigned rule);
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize& requestedSize) override;

protected:
    unsigned m_rule;
    QPixmapCache m_pixCache;
    std::vector<std::pair<size_t, std::vector<bool>>> m_cache;
    const size_t m_w, m_h;
};

#endif // RENDER_H
