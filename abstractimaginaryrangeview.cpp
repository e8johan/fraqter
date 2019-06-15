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
    , m_isDragging(false)
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

bool AbstractImaginaryRangeView::canZoom() const
{
    return true;
}

void AbstractImaginaryRangeView::setTopLeftCoord(FComplex topLeftCoord)
{
    if (m_topLeftCoord == topLeftCoord)
        return;

    m_topLeftCoord = topLeftCoord;
    if (autoRedraw())
        redrawBuffer();
    emit topLeftCoordChanged(m_topLeftCoord);
}

void AbstractImaginaryRangeView::setBottomRightCoord(FComplex bottomRightCoord)
{
    if (m_bottomRightCoord == bottomRightCoord)
        return;

    m_bottomRightCoord = bottomRightCoord;
    if (autoRedraw())
        redrawBuffer();
    emit bottomRightCoordChanged(m_bottomRightCoord);
}

void AbstractImaginaryRangeView::zoomIn()
{
    FComplex center = FComplex((m_topLeftCoord.real+m_bottomRightCoord.real)/2.0, (m_topLeftCoord.imag+m_bottomRightCoord.imag)/2.0);
    FReal width = m_bottomRightCoord.real-m_topLeftCoord.real;
    FReal height = m_bottomRightCoord.imag - m_topLeftCoord.imag;

    // Half width (as we both add and subtract from center
    // New half width is one quarter, which means a 2x factor
    width /= 4.0;
    height /= 4.0;

    m_topLeftCoord = FComplex(center.real-width, center.imag-height);
    m_bottomRightCoord = FComplex(center.real+width, center.imag+height);

    // TODO what about autoredraw?
    redrawBuffer();
}

void AbstractImaginaryRangeView::zoomOut()
{
    FComplex center = FComplex((m_topLeftCoord.real+m_bottomRightCoord.real)/2.0, (m_topLeftCoord.imag+m_bottomRightCoord.imag)/2.0);
    FReal width = m_bottomRightCoord.real-m_topLeftCoord.real;
    FReal height = m_bottomRightCoord.imag - m_topLeftCoord.imag;

    // Half width (as we both add and subtract from center
    // New half width old width, which means a 2x factor

    m_topLeftCoord = FComplex(center.real-width, center.imag-height);
    m_bottomRightCoord = FComplex(center.real+width, center.imag+height);

    // TODO what about autoredraw?
    redrawBuffer();
}

void AbstractImaginaryRangeView::paintEvent(QPaintEvent *e)
{
    if (!buffer().isNull())
    {
        QPainter p(this);
        p.drawImage(e->rect(), buffer(), e->rect());

        if (m_isDragging)
        {
            p.setPen(Qt::red);
            p.drawRect(rectFromPoints(m_dragStart, m_dragLast));
        }
    }
    else {
        QPainter p(this);
        p.setBrush(Qt::darkGray);
        p.drawRect(e->rect());
    }
}

void AbstractImaginaryRangeView::resizeEvent(QResizeEvent *)
{
    // TODO can we stretch the current buffer?
    if (autoRedraw())
        redrawBuffer();
}

void AbstractImaginaryRangeView::mouseMoveEvent(QMouseEvent *e)
{
    emit statusBarUpdate(convertFComplexToString(posToComplex(e->pos().x(), e->pos().y())));

    if (m_isDragging)
    {
        QRect updateRect = rectFromPoints(m_dragStart, m_dragLast).united(rectFromPoints(m_dragStart, e->pos()));
        updateRect.setWidth(updateRect.width()+1);
        updateRect.setHeight(updateRect.height()+1);
        update(updateRect);
        m_dragLast = e->pos();
    }
}

void AbstractImaginaryRangeView::mousePressEvent(QMouseEvent *e)
{
    m_dragLast = m_dragStart = e->pos();
    m_isDragging = true;
}

void AbstractImaginaryRangeView::mouseReleaseEvent(QMouseEvent *e)
{
    FComplex start = posToComplex(m_dragStart.x(), m_dragStart.y());
    FComplex end = posToComplex(e->pos().x(), e->pos().y());

    m_isDragging = false;
    update(QRect(m_dragStart, m_dragLast).intersected(QRect(m_dragStart, e->pos())));

    m_topLeftCoord = FComplex(f_min(start.real, end.real), f_min(start.imag, end.imag));
    m_bottomRightCoord = FComplex(f_max(start.real, end.real), f_max(start.imag, end.imag));

    // TODO what about autoredraw?
    redrawBuffer();
}

FComplex AbstractImaginaryRangeView::posToComplex(int x, int y) const
{
    return FComplex(double(x)/double(width())*(m_bottomRightCoord.real-m_topLeftCoord.real)+m_topLeftCoord.real,
                    double(y)/double(height())*(m_bottomRightCoord.imag-m_topLeftCoord.imag)+m_topLeftCoord.imag);
}

QRect AbstractImaginaryRangeView::rectFromPoints(const QPoint &a, const QPoint &b) const
{
    return QRect(QPoint(qMin(a.x(), b.x()), qMin(a.y(), b.y())),
                 QPoint(qMax(a.x(), b.x()), qMax(a.y(), b.y())));
}

