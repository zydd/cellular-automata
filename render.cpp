#include <algorithm>
#include <QPainter>

#include "render.h"
#include <QtDebug>

inline std::vector<bool> step(const unsigned rule, std::vector<bool> &prev) {
    std::vector<bool> row(prev.size());
    for (size_t i = 1; i < prev.size()-1; i++)
        row[i] = (rule >> (prev[i-1] << 2 | prev[i] << 1 | prev[i+1])) & 1;
    row[0] = (rule >> (prev[prev.size()-1] << 2 | prev[0] << 1 | prev[1])) & 1;
    row[prev.size()-1] = (rule >> (prev[prev.size()-2] << 2 | prev[prev.size()-1] << 1 | prev[0])) & 1;
    return row;
}

std::vector<std::vector<bool>> automaton(size_t height, unsigned rule, std::vector<bool> &prev) {
    size_t width = prev.size();

    if (width < 1 || height < 1)
        return {};

    std::vector<std::vector<bool>> grid;
    grid.push_back(prev);

    for (size_t i = 1; i < height; ++i)
        grid.push_back(step(rule, grid.back()));

    return grid;
}

Render::Render() : QQuickImageProvider(QQuickImageProvider::Pixmap),
    m_rule(0), m_w(256), m_h(256), m_computed_w(2048)
{
    m_pixCache.setCacheLimit(102400);

    std::vector<bool> begin(m_computed_w);
    begin[m_computed_w/2] = 1;
    m_cache.push_back({0, begin});
}

QPixmap Render::requestPixmap(const QString &id, QSize *size, const QSize &/*requestedSize*/)
{
    QPixmap pixmap;

    if (! m_pixCache.find(id, &pixmap)) {
        auto ids = id.split('/');
        unsigned row = ids[1].toUInt();
        int col = ids[2].toInt();

        qDebug() << "rendering" << row << col;

        auto pos = std::lower_bound(m_cache.rbegin(), m_cache.rend(), row * m_h,
                                    [&](const std::pair<size_t, std::vector<bool>> &e, const size_t &v) {
                                            return e.first > v; });

        if (pos == m_cache.rend())
            throw "m_cache not initialized";

        auto prev = pos->second;
        for (size_t i = 0 ; i < row * m_h - pos->first; ++i)
            prev = step(m_rule, prev);

        auto grid = automaton(m_h, m_rule, prev);
        m_cache.push_back({ (row + 1) * m_h - 1, grid.back() });

        QSize s(static_cast<int>(m_w), static_cast<int>(m_h));
        pixmap = QPixmap(s);
        pixmap.fill(Qt::white);

        QPainter painter(&pixmap);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::SolidPattern);

        for (int y = 0; y < s.height(); ++y) {
            for (int x = 0; x < s.width(); x++) {
                if (grid[static_cast<size_t>(y)][static_cast<size_t>(col) * m_w % m_computed_w + static_cast<size_t>(x)])
                    painter.drawPoint(x, y);
            }
        }

        m_pixCache.insert(id, pixmap);
    }

    *size = pixmap.size();
    return pixmap;
}

void Render::setRule(unsigned rule)
{
    m_rule = rule;
    m_pixCache.clear();
    m_cache.clear();

    std::vector<bool> begin(m_computed_w, {});
    if (m_random) {
        srand(42);
        for (size_t i = 0; i < begin.size(); ++i)
            begin[i] = rand() & 1;
    } else {
        begin[m_computed_w/2] = 1;
    }
    m_cache.push_back({0, begin});
}

