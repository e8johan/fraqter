#ifndef ABSTRACTFRACTAL_H
#define ABSTRACTFRACTAL_H

#include <QObject>
#include <QImage>

class AbstractFractal : public QObject
{
    Q_OBJECT

public:
    explicit AbstractFractal(QObject *parent = nullptr);

    const QImage &buffer() const;

    virtual bool canZoom() const = 0;
    virtual void zoom(QSize, QRect);
    virtual void zoomIn(QSize, QPoint);
    virtual void zoomOut(QSize, QPoint);

    virtual void generateNewBuffer(const QSize &) = 0;

public slots:
    void setBuffer(const QImage &);

signals:
    void bufferNeedsRepaint();
    void bufferUpdated();

private:
    QImage m_buffer;
};

#endif // ABSTRACTFRACTAL_H
