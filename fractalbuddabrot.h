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
#ifndef FRACTALBUDDABROT_H
#define FRACTALBUDDABROT_H

#include "abstractimaginaryrangefractal.h"

class FractalBuddabrot : public AbstractImaginaryRangeFractal
{
    Q_OBJECT

    Q_PROPERTY(qreal iterationsFactor READ iterationsFactor WRITE setIterationsFactor NOTIFY iterationsFactorChanged)
    Q_PROPERTY(int maxIterations READ maxIterations WRITE setMaxIterations NOTIFY maxIterationsChanged)

public:
    explicit FractalBuddabrot(QObject *parent = nullptr);

    virtual void generateNewBuffer(const QSize &) override;

    qreal iterationsFactor() const;
    int maxIterations() const;

public slots:
    void setIterationsFactor(qreal iterationsFactor);
    void setMaxIterations(int maxIterations);

signals:
    void iterationsFactorChanged(qreal iterationsFactor);
    void maxIterationsChanged(int maxIterations);

private:
    qreal m_iterationsFactor;
    int m_maxIterations;
};

#endif // FRACTALBUDDABROT_H
