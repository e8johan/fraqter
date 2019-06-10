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
#ifndef ABSTRACTFRACTALVIEW_H
#define ABSTRACTFRACTALVIEW_H

#include <QWidget>
#include <QImage>

class AbstractFractalView : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool autoRedraw READ autoRedraw WRITE setAutoRedraw NOTIFY autoRedrawChanged SCRIPTABLE false)

public:
    explicit AbstractFractalView(QWidget *parent = nullptr);
    bool autoRedraw() const;

public slots:
    virtual void forceRedraw() = 0;
    void setAutoRedraw(bool autoRedraw);

signals:
    void autoRedrawChanged(bool autoRedraw);

    void statusBarUpdate(const QString &);

private:
    bool m_autoRedraw;
};

#endif // ABSTRACTFRACTALVIEW_H
