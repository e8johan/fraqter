/*
 * Fraqter - a fractal exploration program
 * Copyright (C) 2019 Johan Thelin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "abstractattractorview.h"

#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>

AbstractAttractorView::AbstractAttractorView(QWidget *parent)
    : AbstractFractalView(parent)
    , m_iterations(1000000)
{
}

long AbstractAttractorView::iterations() const
{
    return m_iterations;
}

void AbstractAttractorView::setIterations(long iterations)
{
    if (m_iterations == iterations)
        return;

    m_iterations = iterations;
    if (autoRedraw())
        redrawBuffer();
    emit iterationsChanged(m_iterations);
}

void AbstractAttractorView::paintEvent(QPaintEvent *e)
{
    if (!m_buffer.isNull())
    {
        QPainter p(this);
        p.drawImage(e->rect(), m_buffer, e->rect());
    }
    else {
        QPainter p(this);
        p.setBrush(Qt::darkGray);
        p.drawRect(e->rect());
    }
}

void AbstractAttractorView::resizeEvent(QResizeEvent *)
{
    if (autoRedraw())
        redrawBuffer();
}

void AbstractAttractorView::mouseMoveEvent(QMouseEvent *)
{

}

void AbstractAttractorView::forceRedraw()
{
    redrawBuffer();
}

void AbstractAttractorView::redrawBuffer()
{
    m_buffer = QImage(size(), QImage::Format_ARGB32);

    QVector<QVector<int> > counterBuffer(m_buffer.width(), QVector<int>(m_buffer.height()));
    long iterations = m_iterations;
    int maxHits = 1;

    FReal x, y, nx, ny;
    x = y = 0;

    while (iterations-- > 0)
    {
        iterate(x, y, &nx, &ny);

        int px = int(m_buffer.width()*(nx+2.0)/4.0);
        int py = int(m_buffer.height()*(ny+2.0)/4.0);

        if (px >= 0 && px < m_buffer.width() && py >= 0 && py < m_buffer.height() )
        {
            counterBuffer[px][py]++;
            if (counterBuffer[px][py] > maxHits)
                maxHits = counterBuffer[px][py];
        }

        x = nx;
        y = ny;
    }

    for (int px=0; px<m_buffer.width(); ++px)
        for (int py=0; py<m_buffer.height(); ++py)
        {
            qreal f = log10((counterBuffer[px][py]==0?1.0:1.2)+8.8*qreal(counterBuffer[px][py])/qreal(maxHits));
            QColor color = QColor(int(255*f), int(255*f), int(64*(1.0-f)));
            m_buffer.setPixelColor(px, py, color);
        }


    update();
}
