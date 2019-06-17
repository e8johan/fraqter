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
#include "fractalbuddabrot.h"
#include "fractalbuddabrot.h"

#include <QVector>
#include <QRandomGenerator>
#include <QColor>

FractalBuddabrot::FractalBuddabrot(QObject *parent)
    : AbstractImaginaryRangeFractal(parent)
    , m_iterationsFactor(2.0)
    , m_maxIterations(50)
{

}

qreal FractalBuddabrot::iterationsFactor() const
{
    return m_iterationsFactor;
}

int FractalBuddabrot::maxIterations() const
{
    return m_maxIterations;
}

void FractalBuddabrot::setIterationsFactor(qreal iterationsFactor)
{
    if (qFuzzyCompare(m_iterationsFactor, iterationsFactor))
        return;

    m_iterationsFactor = iterationsFactor;
/* TODO    if (autoRedraw())
        redrawBuffer(); */
    emit iterationsFactorChanged(m_iterationsFactor);
}

void FractalBuddabrot::setMaxIterations(int maxIterations)
{
    if (m_maxIterations == maxIterations)
        return;

    m_maxIterations = maxIterations;
    /* TODO    if (autoRedraw())
            redrawBuffer(); */
    emit maxIterationsChanged(m_maxIterations);
}

void FractalBuddabrot::generateNewBuffer(const QSize &size)
{
    m_buffer = QImage(size, QImage::Format_ARGB32);
    QVector<QVector<int> > counterBuffer(m_buffer.width(), QVector<int>(m_buffer.height()));
    long long iterations = static_cast<long long>(double(m_buffer.width() * m_buffer.height()) * iterationsFactor());
    int maxHits = 1;

    QRandomGenerator rand;

    while (iterations-- > 0)
    {
        QVector<FComplex> coords(maxIterations());

        const FComplex c0(double(rand.bounded(-20000, 20000))/10000.0,
                          double(rand.bounded(-20000, 20000))/10000.0);

        FComplex c = c0;
        const int imax = maxIterations();

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

                    const int x = int((crd.real - topLeftCoord().real)/(bottomRightCoord().real - topLeftCoord().real)*double(m_buffer.width()));
                    const int y = int((crd.imag - topLeftCoord().imag)/(bottomRightCoord().imag - topLeftCoord().imag)*double(m_buffer.height()));

                    if (x>=0 && y>=0 && x<m_buffer.width() && y<m_buffer.height())
                    {
                        counterBuffer[x][y] ++;
                        if (counterBuffer[x][y] > maxHits)
                            maxHits = counterBuffer[x][y];
                    }
                }

                break;
            }

            c = nc;
        }
    }

    for (int x=0; x<m_buffer.width(); ++x)
        for (int y=0; y<m_buffer.height(); ++y)
        {
            qreal f = qreal(counterBuffer[x][y])/qreal(maxHits);
            QColor color = QColor(int(255*f), int(255*f), int(64*(1.0-f)));
            m_buffer.setPixelColor(x, y, color);
        }

    emit bufferUpdated();
}

const QImage &FractalBuddabrot::buffer() const
{
    return m_buffer;
}
