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
#include "fractalmandelbrot.h"

FractalMandelbrot::FractalMandelbrot(QObject *parent)
    : AbstractImaginaryRangeEscapeFractal(parent)
{

}

double FractalMandelbrot::iterate(const FComplex &c0) const
{
    FComplex c = c0;
    const int imax = maxIterations();

    int i;
    for (i=0; i<imax; ++i)
    {
        FComplex nc(c.real*c.real - c.imag*c.imag + c0.real, 2*c.real*c.imag+c0.imag);
        if (nc.real*nc.real + nc.imag*nc.imag > 4.0)
            break;

        c = nc;
    }
    return double(i)/double(imax);
}
