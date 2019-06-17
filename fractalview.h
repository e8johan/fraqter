#ifndef FRACTALVIEW_H
#define FRACTALVIEW_H

#include <QWidget>

class AbstractFractal;

class FractalView : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool autoRedraw READ autoRedraw WRITE setAutoRedraw NOTIFY autoRedrawChanged)

public:
    explicit FractalView(AbstractFractal *fractal, QWidget *parent = nullptr);

    bool canZoom() const;
    AbstractFractal *fractal() const;

    bool autoRedraw() const;

public slots:
    virtual void zoomIn();
    virtual void zoomOut();

    void forceRedraw();
    void setAutoRedraw(bool autoRedraw);

signals:
    void autoRedrawChanged(bool autoRedraw);

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private slots:
    void onBufferChanged();
    void onBufferNeedsRepaint();

private:
    static QRect rectFromPoints(const QPoint &a, const QPoint &b);

    AbstractFractal *m_fractal;

    bool m_isDragging;
    QPoint m_dragStart, m_dragLast;
    bool m_autoRedraw;
};

#endif // FRACTALVIEW_H
