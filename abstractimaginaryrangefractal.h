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
#ifndef ABSTRACTIMAGINARYRANGEFRACTAL_H
#define ABSTRACTIMAGINARYRANGEFRACTAL_H

#include "abstractfractal.h"
#include "fmath.h"

class AbstractImaginaryRangeFractal : public AbstractFractal
{
    Q_OBJECT

    Q_PROPERTY(FComplex topLeftCoord READ topLeftCoord WRITE setTopLeftCoord NOTIFY topLeftCoordChanged)
    Q_PROPERTY(FComplex bottomRightCoord READ bottomRightCoord WRITE setBottomRightCoord NOTIFY bottomRightCoordChanged)

public:
    explicit AbstractImaginaryRangeFractal(QObject *parent = nullptr);

    FComplex topLeftCoord() const;
    FComplex bottomRightCoord() const;

    virtual bool canZoom() const override;
    virtual void zoom(QSize, QRect) override;
    virtual void zoomIn(QSize, QPoint) override;
    virtual void zoomOut(QSize, QPoint) override;

public slots:
    void setTopLeftCoord(FComplex topLeftCoord);
    void setBottomRightCoord(FComplex bottomRightCoord);

signals:
    void topLeftCoordChanged(FComplex topLeftCoord);
    void bottomRightCoordChanged(FComplex bottomRightCoord);

private:
    FComplex posToComplex(const QSize &s, int x, int y) const;

    FComplex m_topLeftCoord;
    FComplex m_bottomRightCoord;
};

#endif // ABSTRACTIMAGINARYRANGEFRACTAL_H
