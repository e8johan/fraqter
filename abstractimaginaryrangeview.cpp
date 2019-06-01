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
#include "abstractimaginaryrangeview.h"

#include <QPaintEvent>
#include <QResizeEvent>

#include <QPainter>

AbstractImaginaryRangeView::AbstractImaginaryRangeView(QWidget *parent) : AbstractFractalView(parent)
{

}

void AbstractImaginaryRangeView::paintEvent(QPaintEvent *e)
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

void AbstractImaginaryRangeView::resizeEvent(QResizeEvent *e)
{
    m_buffer = QImage(e->size(), QImage::Format_ARGB32);

    const QPair<double, double> m_min(-2.1, -1.3);
    const QPair<double, double> m_max(0.6, 1.3);

    for (int x=0; x<m_buffer.width(); ++x)
        for (int y=0; y<m_buffer.height(); ++y)
        {
            QPair<double, double> c0(double(x)/double(m_buffer.width())*(m_max.first-m_min.first)+m_min.first, double(y)/double(m_buffer.height())*(m_max.second-m_min.second)+m_min.second);
            int c = int(255.0 * iterate(c0));
            m_buffer.setPixelColor(x, y, QColor(c, c, c));
        }
}
