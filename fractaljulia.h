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
#ifndef FRACTALJULIA_H
#define FRACTALJULIA_H

#include "abstractimaginaryrangeescapeview.h"

class FractalJulia : public AbstractImaginaryRangeEscapeView
{
    Q_OBJECT

    Q_PROPERTY(FComplex c READ cValue WRITE setCValue NOTIFY cValueChanged SCRIPTABLE true)

public:
    explicit FractalJulia(QWidget *parent = nullptr);

    FComplex cValue() const;

public slots:
    void setCValue(FComplex c);

signals:
    void cValueChanged(FComplex c);

protected:
    virtual double iterate(const FComplex &z0) const override;

private:
    FComplex m_cValue;
};

#endif // FRACTALJULIA_H
