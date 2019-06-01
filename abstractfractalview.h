#ifndef ABSTRACTFRACTALVIEW_H
#define ABSTRACTFRACTALVIEW_H

#include <QWidget>
#include <QImage>

class AbstractFractalView : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractFractalView(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);

private:
    QImage m_buffer;
};

#endif // ABSTRACTFRACTALVIEW_H
