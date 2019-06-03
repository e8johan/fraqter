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
#ifndef ABSTRACTIMAGINARYRANGEVIEW_H
#define ABSTRACTIMAGINARYRANGEVIEW_H

#include "abstractfractalview.h"
#include "fmath.h"

class AbstractImaginaryRangeView : public AbstractFractalView
{
    Q_OBJECT

    Q_PROPERTY(FComplex topLeftCoord READ topLeftCoord WRITE setTopLeftCoord NOTIFY topLeftCoordChanged SCRIPTABLE true)
    Q_PROPERTY(FComplex bottomRightCoord READ bottomRightCoord WRITE setBottomRightCoord NOTIFY bottomRightCoordChanged SCRIPTABLE true)
    Q_PROPERTY(int maxIterations READ maxIterations WRITE setMaxIterations NOTIFY maxIterationsChanged SCRIPTABLE true)

public:
    explicit AbstractImaginaryRangeView(QWidget *parent = nullptr);

    FComplex topLeftCoord() const;
    FComplex bottomRightCoord() const;
    int maxIterations() const;

public slots:
    void setTopLeftCoord(FComplex topLeftCoord);
    void setBottomRightCoord(FComplex bottomRightCoord);
    void setMaxIterations(int maxIterations);

signals:
    void topLeftCoordChanged(FComplex topLeftCoord);
    void bottomRightCoordChanged(FComplex bottomRightCoord);
    void maxIterationsChanged(int maxIterations);

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

    void redrawBuffer();

    virtual double iterate(const FComplex &) const = 0;

private:
    QImage m_buffer;

    FComplex m_topLeftCoord;
    FComplex m_bottomRightCoord;
    int m_maxIterations;
};

#endif // ABSTRACTIMAGINARYRANGEVIEW_H
