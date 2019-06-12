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
#ifndef ABSTRACTATTRACTORVIEW_H
#define ABSTRACTATTRACTORVIEW_H

#include "abstractfractalview.h"
#include "fmath.h"

#include <QImage>

class AbstractAttractorView : public AbstractFractalView
{
    Q_OBJECT

    Q_PROPERTY(long iterations READ iterations WRITE setIterations NOTIFY iterationsChanged)

public:
    explicit AbstractAttractorView(QWidget *parent = nullptr);

    long iterations() const;

public slots:
    void setIterations(long iterations);

signals:
    void iterationsChanged(long iterations);

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

    virtual void forceRedraw() override;
    void redrawBuffer();
    virtual void iterate(FReal x, FReal y, FReal *nx, FReal *ny) const = 0;

private:
    QImage m_buffer;
    long m_iterations;
};

#endif // ABSTRACTATTRACTORVIEW_H
