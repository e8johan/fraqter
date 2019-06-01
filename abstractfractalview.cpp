#include "abstractfractalview.h"

#include <QPaintEvent>
#include <QResizeEvent>

#include <QPainter>

AbstractFractalView::AbstractFractalView(QWidget *parent) : QWidget(parent)
{

}

void AbstractFractalView::paintEvent(QPaintEvent *e)
{
    if (!m_buffer.isNull())
    {
        QPainter p(this);
        p.drawImage(e->rect(), m_buffer, e->rect());
    }
    else {
        QPainter p(this);
        p.setBrush(Qt::darkGray);
        p.drawRect(e->rect());
    }
}

void AbstractFractalView::resizeEvent(QResizeEvent *e)
{
    m_buffer = QImage(e->size(), QImage::Format_ARGB32);

    const QPair<double, double> m_min(-2.1, -1.3);
    const QPair<double, double> m_max(0.6, 1.3);
    const int imax = 255;

    for (int x=0; x<m_buffer.width(); ++x)
        for (int y=0; y<m_buffer.height(); ++y)
        {
            QPair<double, double> c0(double(x)/double(m_buffer.width())*(m_max.first-m_min.first)+m_min.first, double(y)/double(m_buffer.height())*(m_max.second-m_min.second)+m_min.second);
            QPair<double, double> c = c0;

            int i;
            for (i=0; i<imax; ++i)
            {
                QPair<double, double> nc(c.first*c.first - c.second*c.second + c0.first, 2*c.first*c.second+c0.second);
                if (nc.first*nc.first + nc.second+nc.second > 4.0)
                {
                    break;
                }

                c = nc;
            }

            m_buffer.setPixelColor(x, y, QColor(i, i, i));
        }

    //m_buffer.fill(Qt::red);
}
