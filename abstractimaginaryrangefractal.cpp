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
#include "abstractimaginaryrangefractal.h"

#include <QPaintEvent>
#include <QResizeEvent>

#include <QPainter>

AbstractImaginaryRangeFractal::AbstractImaginaryRangeFractal(QObject *parent)
    : AbstractFractal(parent)
    , m_topLeftCoord(-2, -2)
    , m_bottomRightCoord(2, 2)
{
}

FComplex AbstractImaginaryRangeFractal::topLeftCoord() const
{
    return m_topLeftCoord;
}

FComplex AbstractImaginaryRangeFractal::bottomRightCoord() const
{
    return m_bottomRightCoord;
}

bool AbstractImaginaryRangeFractal::canZoom() const
{
    return true;
}

void AbstractImaginaryRangeFractal::zoom(QSize size, QRect r)
{
    FComplex t = posToComplex(size, r.topLeft().x(), r.topLeft().y());
    m_bottomRightCoord = posToComplex(size, r.bottomRight().x(), r.bottomRight().y());
    m_topLeftCoord = t;

    // Pre-zooming for UX
    QImage b = buffer().copy(r);
    setBuffer(b.scaled(size));

    emit bufferNeedsRepaint();
}

void AbstractImaginaryRangeFractal::setTopLeftCoord(FComplex topLeftCoord)
{
    if (m_topLeftCoord == topLeftCoord)
        return;

    m_topLeftCoord = topLeftCoord;

    emit bufferNeedsRepaint();
    emit topLeftCoordChanged(m_topLeftCoord);
}

void AbstractImaginaryRangeFractal::setBottomRightCoord(FComplex bottomRightCoord)
{
    if (m_bottomRightCoord == bottomRightCoord)
        return;

    m_bottomRightCoord = bottomRightCoord;

    emit bufferNeedsRepaint();
    emit bottomRightCoordChanged(m_bottomRightCoord);
}

void AbstractImaginaryRangeFractal::zoomIn(QSize, QPoint)
{
    // TODO zoom around given point
    FComplex center = FComplex((m_topLeftCoord.real+m_bottomRightCoord.real)/2.0, (m_topLeftCoord.imag+m_bottomRightCoord.imag)/2.0);
    FReal width = m_bottomRightCoord.real-m_topLeftCoord.real;
    FReal height = m_bottomRightCoord.imag - m_topLeftCoord.imag;

    // Half width (as we both add and subtract from center
    // New half width is one quarter, which means a 2x factor
    width /= 4.0;
    height /= 4.0;

    m_topLeftCoord = FComplex(center.real-width, center.imag-height);
    m_bottomRightCoord = FComplex(center.real+width, center.imag+height);

    emit bufferNeedsRepaint();
}

void AbstractImaginaryRangeFractal::zoomOut(QSize, QPoint)
{
    // TODO zoom around given point
    FComplex center = FComplex((m_topLeftCoord.real+m_bottomRightCoord.real)/2.0, (m_topLeftCoord.imag+m_bottomRightCoord.imag)/2.0);
    FReal width = m_bottomRightCoord.real-m_topLeftCoord.real;
    FReal height = m_bottomRightCoord.imag - m_topLeftCoord.imag;

    // Half width (as we both add and subtract from center
    // New half width old width, which means a 2x factor

    m_topLeftCoord = FComplex(center.real-width, center.imag-height);
    m_bottomRightCoord = FComplex(center.real+width, center.imag+height);

    emit bufferNeedsRepaint();
}

FComplex AbstractImaginaryRangeFractal::posToComplex(const QSize &s, int x, int y) const
{
    return FComplex(double(x)/double(s.width())*(m_bottomRightCoord.real-m_topLeftCoord.real)+m_topLeftCoord.real,
                    double(y)/double(s.height())*(m_bottomRightCoord.imag-m_topLeftCoord.imag)+m_topLeftCoord.imag);
}

