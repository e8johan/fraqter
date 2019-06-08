#include "fractalbuddabrot.h"

#include <QVector>
#include <QRandomGenerator>
#include <QColor>

FractalBuddabrot::FractalBuddabrot(QWidget *parent)
    : AbstractImaginaryRangeView(parent)
{

}

#include <QtDebug>

void FractalBuddabrot::redrawBuffer()
{
    m_buffer = QImage(size(), QImage::Format_ARGB32);
    QVector<QVector<int> > counterBuffer(m_buffer.width(), QVector<int>(m_buffer.height()));
    long long iterations = m_buffer.width() * m_buffer.height() * 10;
    const int maxIterations = 50;

    QRandomGenerator rand;

    while (iterations-- > 0)
    {
        QVector<FComplex> coords(maxIterations);

        const FComplex c0(double(rand.bounded(-20000, 20000))/10000.0,
                          double(rand.bounded(-20000, 20000))/10000.0);

        FComplex c = c0;
        const int imax = maxIterations;

        int i;
        for (i=0; i<imax; ++i)
        {
            FComplex nc(c.real*c.real - c.imag*c.imag + c0.real, 2*c.real*c.imag+c0.imag);

            coords[i] = nc;

            if (nc.real*nc.real + nc.imag*nc.imag > 4.0)
            {
                for (int j=0; j<i; ++j)
                {
                    const FComplex &crd = coords[j];

                    const int x = (crd.real - topLeftCoord().real)/(bottomRightCoord().real - topLeftCoord().real)*m_buffer.width();
                    const int y = (crd.imag - topLeftCoord().imag)/(bottomRightCoord().imag - topLeftCoord().imag)*m_buffer.height();

                    counterBuffer[x][y] += 1;
                }

                break;
            }

            c = nc;
        }
    }

    for (int x=0; x<m_buffer.width(); ++x)
        for (int y=0; y<m_buffer.height(); ++y)
        {
            QColor color = QColor(qMin(255, counterBuffer[x][y]), qMin(255, counterBuffer[x][y]), (255-qMin(255, counterBuffer[x][y]))/4);
            m_buffer.setPixelColor(x, y, color);
        }
}

const QImage &FractalBuddabrot::buffer() const
{
    return m_buffer;
}
