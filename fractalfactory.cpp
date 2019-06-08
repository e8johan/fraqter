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
#include "fractalfactory.h"

#include "fractalmandelbrot.h"
#include "fractaljulia.h"
#include "fractalbuddabrot.h"

FractalFactory *FractalFactory::instance()
{
    static FractalFactory inst;
    return &inst;
}

int FractalFactory::rowCount(const QModelIndex &index) const
{
    if (index.isValid())
        return 0;
    else
        return m_fractalIds.count();
}

QVariant FractalFactory::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && index.column() == 0 && index.row() >= 0 && index.row() < m_fractalIds.count())
    {
        switch(role)
        {
        case Qt::DisplayRole:
            return m_fractalIds.at(index.row());
        }
    }

    return QVariant();
}

AbstractFractalView *FractalFactory::createView(const QString fractalId)
{
    if (fractalId == QStringLiteral("Mandelbrot"))
        return new FractalMandelbrot();
    else if (fractalId == QStringLiteral("Julia"))
        return new FractalJulia();
    else if (fractalId == QStringLiteral("Buddabrot"))
        return new FractalBuddabrot();
    else
        return nullptr;
}

FractalFactory::FractalFactory()
{
    m_fractalIds << QStringLiteral("Mandelbrot")
                 << QStringLiteral("Julia")
                 << QStringLiteral("Buddabrot");
}
