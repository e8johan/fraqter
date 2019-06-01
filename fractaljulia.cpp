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
#include "fractaljulia.h"

FractalJulia::FractalJulia(QWidget *parent) : AbstractImaginaryRangeView(parent)
{

}

double FractalJulia::iterate(QPair<double, double> z0) const
{
    const QPair<double, double> c(-0.8, 0.156);
    QPair<double, double> z = z0;
    const int imax = 500;

    int i;
    for (i=0; i<imax; ++i)
    {
        QPair<double, double> nz(z.first*z.first-z.second*z.second+c.first, 2*z.first*z.second+c.second);
        if (nz.first*nz.first + nz.second+nz.second > 4.0)
            break;

        z = nz;
    }
    return double(i)/double(imax);
}
