#include "abstractfractal.h"

AbstractFractal::AbstractFractal(QObject *parent)
    : QObject(parent)
{
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
