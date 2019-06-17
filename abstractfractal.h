#ifndef ABSTRACTFRACTAL_H
#define ABSTRACTFRACTAL_H

#include <QObject>
#include <QImage>

class AbstractFractal : public QObject
{
    Q_OBJECT

public:
    explicit AbstractFractal(QObject *parent = nullptr);

    virtual bool canZoom() const = 0;
    virtual void zoom(QSize, QRect);
    virtual void zoomIn(QSize, QPoint);
    virtual void zoomOut(QSize, QPoint);

    virtual const QImage &buffer() const = 0;
    virtual void generateNewBuffer(const QSize &) = 0;

signals:
    void bufferNeedsRepaint();
    void bufferUpdated();
};

#endif // ABSTRACTFRACTAL_H
