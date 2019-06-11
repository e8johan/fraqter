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
#ifndef FRACTALDEJONGATTRACTOR_H
#define FRACTALDEJONGATTRACTOR_H

#include "abstractattractorview.h"

class FractalDeJongAttractor : public AbstractAttractorView
{
    Q_OBJECT

public:
    explicit FractalDeJongAttractor(QWidget *parent = nullptr);

protected:
    virtual void iterate(FReal x, FReal y, FReal *nx, FReal *ny) const override;

private:
    FReal m_factors[4];
};

#endif // FRACTALDEJONGATTRACTOR_H
