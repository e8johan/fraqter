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

AbstractImaginaryRangeView::AbstractImaginaryRangeView(QWidget *parent)
    : AbstractFractalView(parent)
    , m_topLeftCoord(-2, -2)
    , m_bottomRightCoord(2, 2)
{
    setMouseTracking(true);
}

FComplex AbstractImaginaryRangeView::topLeftCoord() const
{
    return m_topLeftCoord;
}

FComplex AbstractImaginaryRangeView::bottomRightCoord() const
{
    return m_bottomRightCoord;
}

void AbstractImaginaryRangeView::setTopLeftCoord(FComplex topLeftCoord)
{
    if (m_topLeftCoord == topLeftCoord)
        return;

    m_topLeftCoord = topLeftCoord;
    redrawBuffer();
    emit topLeftCoordChanged(m_topLeftCoord);
}

void AbstractImaginaryRangeView::setBottomRightCoord(FComplex bottomRightCoord)
{
    if (m_bottomRightCoord == bottomRightCoord)
        return;

    m_bottomRightCoord = bottomRightCoord;
    redrawBuffer();
    emit bottomRightCoordChanged(m_bottomRightCoord);
}

void AbstractImaginaryRangeView::paintEvent(QPaintEvent *e)
{
    if (!buffer().isNull())
    {
        QPainter p(this);
        p.drawImage(e->rect(), buffer(), e->rect());
    }
    else {
        QPainter p(this);
        p.setBrush(Qt::darkGray);
        p.drawRect(e->rect());
    }
}

void AbstractImaginaryRangeView::resizeEvent(QResizeEvent *)
{
    redrawBuffer();
}

void AbstractImaginaryRangeView::mouseMoveEvent(QMouseEvent *e)
{
    FComplex pos(double(e->pos().x())/double(width())*(m_bottomRightCoord.real-m_topLeftCoord.real)+m_topLeftCoord.real,
                 double(e->pos().y())/double(height())*(m_bottomRightCoord.imag-m_topLeftCoord.imag)+m_topLeftCoord.imag);

    emit statusBarUpdate(convertFComplexToString(pos));
}

