#ifndef FRACTALJULIA_H
#define FRACTALJULIA_H

#include "abstractimaginaryrangeview.h"

class FractalJulia : public AbstractImaginaryRangeView
{
public:
    explicit FractalJulia(QWidget *parent = nullptr);

protected:
    virtual double iterate(QPair<double, double> z0) const override;
};

#endif // FRACTALJULIA_H
