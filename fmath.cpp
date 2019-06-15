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
#include "fmath.h"

FComplex::FComplex()
{
    real = 0.0;
    imag = 0.0;
}

FComplex::FComplex(double r, double i)
{
    real = r;
    imag = i;
}

bool operator==(FComplex a, FComplex b)
{
    return (a.real == b.real) && (a.imag == b.imag);
}

QString convertFComplexToString(FComplex v)
{
    if (v.imag < 0.0)
        return QString::number(v.real, 'e') + "-i" + QString::number(-v.imag, 'e');
    else
        return QString::number(v.real, 'e') + "+i" + QString::number(v.imag, 'e');
}

void initializeFMath()
{
    qRegisterMetaType<FComplex>();
    QMetaType::registerConverter<FComplex, QString>(convertFComplexToString);
}

FReal f_cos(FReal x)
{
    return cos(x);
}

FReal f_sin(FReal x)
{
    return sin(x);
}

FReal f_min(FReal a, FReal b)
{
    if (a < b)
        return a;
    else
        return b;
}

FReal f_max(FReal a, FReal b)
{
    if (a > b)
        return a;
    else
        return b;
}
