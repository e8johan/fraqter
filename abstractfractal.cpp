#include "abstractfractal.h"

AbstractFractal::AbstractFractal(QObject *parent)
    : QObject(parent)
{
}

const QImage &AbstractFractal::buffer() const
{
    return m_buffer;
}

void AbstractFractal::zoom(QSize, QRect)
{
    qDebug("AbstractFractal::zoom unexpected");
}

void AbstractFractal::zoomIn(QSize, QPoint)
{
    qDebug("AbstractFractal::zoomIn unexpected");
}

void AbstractFractal::zoomOut(QSize, QPoint)
{
    qDebug("AbstractFractal::zoomOut unexpected");
}

void AbstractFractal::setBuffer(const QImage &buffer)
{
    m_buffer = buffer;
    emit bufferUpdated();
}
