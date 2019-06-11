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
#include "abstractimaginaryrangeescapeview.h"

AbstractImaginaryRangeEscapeView::AbstractImaginaryRangeEscapeView(QWidget *parent)
    : AbstractImaginaryRangeView(parent)
    , m_maxIterations(1000)
{

}

int AbstractImaginaryRangeEscapeView::maxIterations() const
{
    return m_maxIterations;
}

void AbstractImaginaryRangeEscapeView::setMaxIterations(int maxIterations)
{
    if (m_maxIterations == maxIterations)
        return;

    m_maxIterations = maxIterations;
    if (autoRedraw())
        redrawBuffer();
    emit maxIterationsChanged(m_maxIterations);
}

void AbstractImaginaryRangeEscapeView::forceRedraw()
{
    redrawBuffer();
}

const QImage &AbstractImaginaryRangeEscapeView::buffer() const
{
    return m_buffer;
}

void AbstractImaginaryRangeEscapeView::redrawBuffer()
{
    m_buffer = QImage(size(), QImage::Format_ARGB32);

    for (int x=0; x<m_buffer.width(); ++x)
        for (int y=0; y<m_buffer.height(); ++y)
        {
            FComplex coord(double(x)/double(m_buffer.width())*(bottomRightCoord().real-topLeftCoord().real)+topLeftCoord().real,
                           double(y)/double(m_buffer.height())*(bottomRightCoord().imag-topLeftCoord().imag)+topLeftCoord().imag);
            double f = iterate(coord);
            QColor color = QColor(0, 0, 0);
            if (f < 255.0 / 256.0)
                color = QColor(int(f*255), int(f*255), int((1.0-f)*64));
            m_buffer.setPixelColor(x, y, color);
        }

    update();
}
