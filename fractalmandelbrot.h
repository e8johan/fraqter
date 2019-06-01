#ifndef FRACTALMANDELBROT_H
#define FRACTALMANDELBROT_H

#include "abstractimaginaryrangeview.h"

class FractalMandelbrot : public AbstractImaginaryRangeView
{
public:
    explicit FractalMandelbrot(QWidget *parent = nullptr);

protected:
    virtual double iterate(QPair<double, double> c0) const override;
};

#endif // FRACTALMANDELBROT_H
