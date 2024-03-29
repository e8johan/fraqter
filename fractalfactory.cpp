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
#include "fractaldejongattractor.h"
#include "fractalcliffordattractor.h"
#include "fractalifs.h"
#include "fractallsystemtriangle.h"
#include "fractallsystemweed.h"
#include "fractallsystemdragoncurve.h"

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

AbstractFractal *FractalFactory::createView(const QString fractalId)
{
    if (fractalId == QStringLiteral("Mandelbrot"))
        return new FractalMandelbrot();
    else if (fractalId == QStringLiteral("Julia"))
        return new FractalJulia();
    else if (fractalId == QStringLiteral("Buddabrot"))
        return new FractalBuddabrot();
    else if (fractalId == QStringLiteral("de Jong Attractor"))
        return new FractalDeJongAttractor();
    else if (fractalId == QStringLiteral("Clifford Attractor"))
        return new FractalCliffordAttractor();
    else if (fractalId == QStringLiteral("IFS Fern"))
        return new FractalIFS();
    else if (fractalId == QStringLiteral("L-System Triangle"))
        return new FractalLSystemTriangle();
    else if (fractalId == QStringLiteral("L-System Weed"))
        return new FractalLSystemWeed();
    else if (fractalId == QStringLiteral("L-System Dragon Curve"))
        return new FractalLSystemDragonCurve();
    else
        return nullptr;
}

FractalFactory::FractalFactory()
{
    m_fractalIds << QStringLiteral("Mandelbrot")
                 << QStringLiteral("Julia")
                 << QStringLiteral("Buddabrot")
                 << QStringLiteral("de Jong Attractor")
                 << QStringLiteral("Clifford Attractor")
                 << QStringLiteral("IFS Fern")
                 << QStringLiteral("L-System Triangle")
                 << QStringLiteral("L-System Weed")
                 << QStringLiteral("L-System Dragon Curve");
}
