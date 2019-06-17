#include "fractalview.h"

#include <QPainter>

#include <QPaintEvent>
#include <QMouseEvent>
#include <QResizeEvent>

#include "abstractfractal.h"

FractalView::FractalView(AbstractFractal *fractal, QWidget *parent)
    : QWidget(parent)
    , m_fractal(fractal)
    , m_isDragging(false)
    , m_autoRedraw(true)
{
    if (m_fractal)
    {
        m_fractal->setParent(this);
        connect(m_fractal, &AbstractFractal::bufferUpdated, this, &FractalView::onBufferChanged);
        connect(m_fractal, &AbstractFractal::bufferNeedsRepaint, this, &FractalView::onBufferNeedsRepaint);
    }
}

bool FractalView::canZoom() const
{
    if (m_fractal)
        return m_fractal->canZoom();
    else {
        return false;
    }
}

AbstractFractal *FractalView::fractal() const
{
    return m_fractal;
}

bool FractalView::autoRedraw() const
{
    return m_autoRedraw;
}

void FractalView::zoomIn()
{
    if (m_fractal)
        m_fractal->zoomIn(size(), QPoint(width()/2, height()/2));
}

void FractalView::zoomOut()
{
    if (m_fractal)
        m_fractal->zoomOut(size(), QPoint(width()/2, height()/2));
}

void FractalView::forceRedraw()
{
    if (m_fractal)
        m_fractal->generateNewBuffer(size());
}

void FractalView::setAutoRedraw(bool autoRedraw)
{
    if (m_autoRedraw == autoRedraw)
        return;

    m_autoRedraw = autoRedraw;
    emit autoRedrawChanged(m_autoRedraw);
}

void FractalView::paintEvent(QPaintEvent *e)
{
    if (m_fractal && !m_fractal->buffer().isNull())
    {
        QPainter p(this);
        p.drawImage(e->rect(), m_fractal->buffer(), e->rect());

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

void FractalView::resizeEvent(QResizeEvent *e)
{
    if (m_fractal)
        m_fractal->generateNewBuffer(e->size());
}

void FractalView::mousePressEvent(QMouseEvent *e)
{
    if (m_fractal && m_fractal->canZoom())
    {
        m_dragLast = m_dragStart = e->pos();
        m_isDragging = true;
    }
}

void FractalView::mouseMoveEvent(QMouseEvent *e)
{
    if (m_isDragging)
    {
        QRect updateRect = rectFromPoints(m_dragStart, m_dragLast).united(rectFromPoints(m_dragStart, e->pos()));
        updateRect.setWidth(updateRect.width()+1);
        updateRect.setHeight(updateRect.height()+1);
        update(updateRect);
        m_dragLast = e->pos();
    }
}

void FractalView::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_isDragging)
    {
        m_isDragging = false;
        QRect updateRect = QRect(m_dragStart, m_dragLast).intersected(QRect(m_dragStart, e->pos()));
        updateRect.setWidth(updateRect.width()+1);
        updateRect.setHeight(updateRect.height()+1);
        update(updateRect);

        if (m_fractal)
            m_fractal->zoom(size(), rectFromPoints(m_dragStart, e->pos()));
    }
}

void FractalView::onBufferChanged()
{
    update();
}

void FractalView::onBufferNeedsRepaint()
{
    if (m_fractal && m_autoRedraw)
        m_fractal->generateNewBuffer(size());
}

QRect FractalView::rectFromPoints(const QPoint &a, const QPoint &b)
{
    return QRect(QPoint(qMin(a.x(), b.x()), qMin(a.y(), b.y())),
                 QPoint(qMax(a.x(), b.x()), qMax(a.y(), b.y())));
}
