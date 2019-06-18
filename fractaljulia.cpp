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

FractalJulia::FractalJulia(QObject *parent)
    : AbstractImaginaryRangeEscapeFractal(new FractalJuliaWorker(), parent)
    , m_cValue(-0.8, 0.156)
{
    dynamic_cast<FractalJuliaWorker*>(worker())->setCValue(cValue());
}

FComplex FractalJulia::cValue() const
{
    return m_cValue;
}

void FractalJulia::setCValue(FComplex c)
{
    if (m_cValue == c)
        return;

    m_cValue = c;
    dynamic_cast<FractalJuliaWorker*>(worker())->setCValue(m_cValue);

    emit bufferNeedsRepaint();
    emit cValueChanged(m_cValue);
}

double FractalJuliaWorker::iterate(int maxIterations, const FComplex &z0) const
{
    const FComplex c = m_rs_cValue;
    FComplex z = z0;
    const int imax = maxIterations;

    int i;
    for (i=0; i<imax; ++i)
    {
        FComplex nz(z.real*z.real-z.imag*z.imag+c.real, 2*z.real*z.imag+c.imag);
        if (nz.real*nz.real + nz.imag*nz.imag > 4.0)
            break;

        z = nz;
    }
    return double(i)/double(imax);
}

FractalJuliaWorker::FractalJuliaWorker()
    : AbstractImaginaryRangeEscapeFractalWorker()
{

}

void FractalJuliaWorker::setCValue(FComplex c)
{
    m_cValue = c;
}

void FractalJuliaWorker::captureRenderState()
{
    m_rs_cValue = m_cValue;
}
