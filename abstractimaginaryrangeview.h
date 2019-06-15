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

    Q_PROPERTY(FComplex topLeftCoord READ topLeftCoord WRITE setTopLeftCoord NOTIFY topLeftCoordChanged)
    Q_PROPERTY(FComplex bottomRightCoord READ bottomRightCoord WRITE setBottomRightCoord NOTIFY bottomRightCoordChanged)

public:
    explicit AbstractImaginaryRangeView(QWidget *parent = nullptr);

    FComplex topLeftCoord() const;
    FComplex bottomRightCoord() const;

    virtual bool canZoom() const override;
    virtual void zoomIn() override;
    virtual void zoomOut() override;

public slots:
    void setTopLeftCoord(FComplex topLeftCoord);
    void setBottomRightCoord(FComplex bottomRightCoord);

signals:
    void topLeftCoordChanged(FComplex topLeftCoord);
    void bottomRightCoordChanged(FComplex bottomRightCoord);

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

    virtual void redrawBuffer() = 0;
    virtual const QImage &buffer() const = 0;

private:
    FComplex posToComplex(int x, int y) const;
    QRect rectFromPoints(const QPoint &a, const QPoint &b) const;

    FComplex m_topLeftCoord;
    FComplex m_bottomRightCoord;

    bool m_isDragging;
    QPoint m_dragStart, m_dragLast;
};

#endif // ABSTRACTIMAGINARYRANGEVIEW_H
