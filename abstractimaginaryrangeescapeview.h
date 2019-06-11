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
#ifndef ABSTRACTIMAGINARYRANGEESCAPEVIEW_H
#define ABSTRACTIMAGINARYRANGEESCAPEVIEW_H

#include "abstractimaginaryrangeview.h"

class AbstractImaginaryRangeEscapeView : public AbstractImaginaryRangeView
{
    Q_OBJECT

    Q_PROPERTY(int maxIterations READ maxIterations WRITE setMaxIterations NOTIFY maxIterationsChanged)

public:
    explicit AbstractImaginaryRangeEscapeView(QWidget *parent = nullptr);

    int maxIterations() const;

public slots:
    void setMaxIterations(int maxIterations);
    virtual void forceRedraw() override;

signals:
    void maxIterationsChanged(int maxIterations);

protected:
    virtual void redrawBuffer() override;
    virtual const QImage &buffer() const override;

    virtual double iterate(const FComplex &) const = 0;

private:
    QImage m_buffer;

    int m_maxIterations;
};

#endif // ABSTRACTIMAGINARYRANGEESCAPEVIEW_H
