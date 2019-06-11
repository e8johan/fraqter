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
#ifndef FMATH_H
#define FMATH_H

#include <QMetaType>
#include <QString>

#include <math.h>

typedef double FReal;

struct FComplex
{
    FComplex();
    FComplex(double, double);

    FReal real, imag;
};

FReal f_sin(FReal x);
FReal f_cos(FReal x);

Q_DECLARE_METATYPE(FComplex)

bool operator==(FComplex a, FComplex b);
QString convertFComplexToString(FComplex);

void initializeFMath();

#endif // FMATH_H
