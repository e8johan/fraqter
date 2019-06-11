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
#include "fractaldejongattractor.h"

FractalDeJongAttractor::FractalDeJongAttractor(QWidget *parent)
    : AbstractAttractorView(parent)
    , m_factors { 1.641, 1.902, 0.316, 1.525 }
{

}

void FractalDeJongAttractor::iterate(FReal x, FReal y, FReal *nx, FReal *ny) const
{
    *nx = f_sin(m_factors[0]*y) - f_cos(m_factors[1]*x);
    *ny = f_sin(m_factors[2]*x) - f_cos(m_factors[3]*y);
}
