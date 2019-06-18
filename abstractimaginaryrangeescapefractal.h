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
#ifndef ABSTRACTIMAGINARYRANGEESCAPEFRACTAL_H
#define ABSTRACTIMAGINARYRANGEESCAPEFRACTAL_H

#include "abstractimaginaryrangefractal.h"

#include <QThread>
#include <QMutex>
#include <QWaitCondition>

/*
 * First threaded rendering fractal -- let's generalize this further
 *
 * The fractal class, Apa, has to be accompanied by a worker class, ApaWorker.
 *
 * The worker class has the same properties as the fractal class, and these
 * must be updated in the constructor of the fractal class, and in all setter
 * functions.
 *
 * Each property must exist twice in the worker class, once as m_foo, and once
 * as m_rs_foo. The first is the current value, while the latter is the values
 * used in the current render job.
 *
 * When sub-classing the worker class, the following methods needs to be implemented:
 *
 * - setters for all properties, setting the m_foo variable
 * - captureRenderState, which copies variables from m_foo to m_rs_foo
 * - iterate - this function renders the actual fractal and must only rely on the
 *   m_rs_foo variables
 *
 * ---
 *
 * Future work:
 *
 * - iterate is local to the imaginary range escape style fractals, so each
 *   fractal type needs to implement the whole threading stuff - not good.
 * - The double state variables is a bit annoying - it might be better to
 *   capture them of the fractal class before rendering.
 * - The setting of worker state in setters and c'tor is error prone - again it
 *   might be better to capture them of the fractal class before rendering.
 * - Would it be possible to do some macro magic to reduce the amount of boiler
 *   plate code?
 *
 */

class AbstractImaginaryRangeEscapeFractalWorker;

class AbstractImaginaryRangeEscapeFractal : public AbstractImaginaryRangeFractal
{
    Q_OBJECT

    Q_PROPERTY(int maxIterations READ maxIterations WRITE setMaxIterations NOTIFY maxIterationsChanged)

public:
    explicit AbstractImaginaryRangeEscapeFractal(AbstractImaginaryRangeEscapeFractalWorker *worker, QObject *parent = nullptr);

    virtual void generateNewBuffer(const QSize &) override;
    virtual const QImage &buffer() const override;

    int maxIterations() const;

public slots:
    void setMaxIterations(int maxIterations);

signals:
    void maxIterationsChanged(int maxIterations);

protected:
    AbstractImaginaryRangeEscapeFractalWorker *worker();

private slots:
    void onRenderDone(const QImage &image);

private:
    AbstractImaginaryRangeEscapeFractalWorker *m_worker;

    QImage m_buffer;

    int m_maxIterations;
};

class AbstractImaginaryRangeEscapeFractalWorker : public QThread
{
    Q_OBJECT

public:
    explicit AbstractImaginaryRangeEscapeFractalWorker();
    ~AbstractImaginaryRangeEscapeFractalWorker() override;

    void setMaxIterations(int);
    void setRange(FComplex, FComplex);

    void render(const QSize &);

signals:
    void renderDone(const QImage &);

protected:
    virtual void run() override;

    virtual void captureRenderState() = 0;
    virtual double iterate(int, const FComplex &) const = 0;

private:
    QMutex m_renderStateMutex;
    QWaitCondition m_renderWait;

    bool m_restart;
    bool m_abort;
    int m_maxIterations;
    FComplex m_topLeftCoord;
    FComplex m_bottomRightCoord;

    QSize m_rs_size;
    int m_rs_maxIterations;
    FComplex m_rs_topLeftCoord;
    FComplex m_rs_bottomRightCoord;
};

#endif // ABSTRACTIMAGINARYRANGEESCAPEFRACTAL_H
