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
#include "abstractimaginaryrangeescapefractal.h"

AbstractImaginaryRangeEscapeFractal::AbstractImaginaryRangeEscapeFractal(AbstractImaginaryRangeEscapeFractalWorker *worker, QObject *parent)
    : AbstractImaginaryRangeFractal(parent)
    , m_worker(worker)
    , m_maxIterations(1000)
{
    m_worker->setParent(this);
    connect(m_worker, &AbstractImaginaryRangeEscapeFractalWorker::renderDone, this, &AbstractImaginaryRangeEscapeFractal::onRenderDone);

    m_worker->setMaxIterations(maxIterations());
}

int AbstractImaginaryRangeEscapeFractal::maxIterations() const
{
    return m_maxIterations;
}

void AbstractImaginaryRangeEscapeFractal::setMaxIterations(int maxIterations)
{
    if (m_maxIterations == maxIterations)
        return;

    m_maxIterations = maxIterations;
    m_worker->setMaxIterations(m_maxIterations);

    emit bufferNeedsRepaint();
    emit maxIterationsChanged(m_maxIterations);
}

AbstractImaginaryRangeEscapeFractalWorker *AbstractImaginaryRangeEscapeFractal::worker()
{
    return m_worker;
}

void AbstractImaginaryRangeEscapeFractal::onRenderDone(const QImage &image)
{
    m_buffer = image;
    emit bufferUpdated();
}

const QImage &AbstractImaginaryRangeEscapeFractal::buffer() const
{
    return m_buffer;
}

void AbstractImaginaryRangeEscapeFractal::generateNewBuffer(const QSize & size)
{
    m_worker->setRange(topLeftCoord(), bottomRightCoord());
    m_worker->render(size);
}

AbstractImaginaryRangeEscapeFractalWorker::AbstractImaginaryRangeEscapeFractalWorker()
    : QThread()
    , m_restart(false)
    , m_abort(false)
    , m_maxIterations(-1)
{
}

AbstractImaginaryRangeEscapeFractalWorker::~AbstractImaginaryRangeEscapeFractalWorker()
{
    m_renderStateMutex.lock();
    m_abort = true;
    m_renderWait.wakeOne();
    m_renderStateMutex.unlock();

    wait();
}

void AbstractImaginaryRangeEscapeFractalWorker::setMaxIterations(int mi)
{
    m_maxIterations = mi;
}

void AbstractImaginaryRangeEscapeFractalWorker::setRange(FComplex tlc, FComplex brc)
{
    m_topLeftCoord = tlc;
    m_bottomRightCoord = brc;
}

void AbstractImaginaryRangeEscapeFractalWorker::render(const QSize &s)
{
    QMutexLocker locker(&m_renderStateMutex);

    m_rs_maxIterations = m_maxIterations;
    m_rs_topLeftCoord = m_topLeftCoord;
    m_rs_bottomRightCoord = m_bottomRightCoord;
    m_rs_size = s;

    if (!isRunning())
    {
        start();
    }
    else
    {
        m_restart = true;
        m_renderWait.wakeOne();
    }
}

void AbstractImaginaryRangeEscapeFractalWorker::run()
{
    while (1)
    {
        m_renderStateMutex.lock();
        QSize size = m_rs_size;
        int maxIterations = m_rs_maxIterations;
        FComplex topLeftCoord = m_rs_topLeftCoord;
        FComplex bottomRightCoord = m_rs_bottomRightCoord;
        captureRenderState();
        m_renderStateMutex.unlock();

        QImage buffer = QImage(size, QImage::Format_ARGB32);

        for (int x=0; x<buffer.width(); ++x)
        {
            if (m_restart)
                break;
            if (m_abort)
                return;

            for (int y=0; y<buffer.height(); ++y)
            {
                FComplex coord(double(x)/double(buffer.width())*(bottomRightCoord.real-topLeftCoord.real)+topLeftCoord.real,
                               double(y)/double(buffer.height())*(bottomRightCoord.imag-topLeftCoord.imag)+topLeftCoord.imag);
                double f = iterate(maxIterations, coord);
                QColor color = QColor(0, 0, 0);
                if (f < 255.0 / 256.0)
                    color = QColor(int(f*255), int(f*255), int((1.0-f)*64));
                buffer.setPixelColor(x, y, color);
            }
        }

        emit renderDone(buffer);

        m_renderStateMutex.lock();
        if (!m_restart)
            m_renderWait.wait(&m_renderStateMutex);
        m_restart = false;
        m_renderStateMutex.unlock();
    }
}
