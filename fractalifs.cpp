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
#include "fractalifs.h"

#include "fmath.h"

#include <QPainter>
#include <QPaintEvent>
#include <QRandomGenerator>

FractalIFS::FractalIFS(QObject *parent)
    : AbstractFractal(parent)
{

}

bool FractalIFS::canZoom() const
{
    return false;
}

void FractalIFS::generateNewBuffer(const QSize &size)
{
    QImage buffer = QImage(size, QImage::Format_ARGB32);
    buffer.fill(Qt::white);

    /*
              a     0.0       0.2      -0.15      0.85
              b     0.0      -0.26      0.28      0.04
              c     0.0       0.23      0.26     -0.04
              d     0.16      0.22      0.24      0.85
              e     0.0       0.0       0.0       0.0
              f     0.0       1.6       0.44      1.6
    probability     0.01      0.07      0.07      0.85
  */

    FReal x, y;
    long iterations = 100000;
    int initIterations = 100;
    QRandomGenerator rand;

    x = 0;
    y = 0;

    while (iterations-- > 0)
    {
        FReal a, b, c, d, e, f;
        int random = rand.bounded(100);

        if (random < 1)
        {
            a = 0;
            b = 0;
            c = 0;
            d = 0.16;
            e = 0;
            f = 0;
        }
        else if (random < 8)
        {
            a = 0.2;
            b = -0.26;
            c = 0.23;
            d = 0.22;
            e = 0;
            f = 1.6;
        }
        else if (random < 15)
        {
            a = -0.15;
            b = 0.28;
            c = 0.26;
            d = 0.24;
            e = 0.0;
            f = 0.44;
        }
        else
        {
            a = 0.85;
            b = 0.04;
            c = -0.04;
            d = 0.85;
            e = 0.0;
            f = 1.6;
        }

        FReal nx = a*x + b*y + e;
        FReal ny = c*x + d*y + f;

        if (initIterations == 0)
        {
            const QColor color = QColor(Qt::darkGreen);
            buffer.setPixelColor(int(buffer.width()*(nx+3.0)/6.0), int(buffer.height()*(11.0-ny)/11.0), color);
        }
        else {
            initIterations --;
        }

        x = nx;
        y = ny;
    }

    setBuffer(buffer);
}
