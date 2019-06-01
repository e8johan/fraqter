#include "fractalmandelbrot.h"

FractalMandelbrot::FractalMandelbrot(QWidget *parent) : AbstractImaginaryRangeView(parent)
{

}

double FractalMandelbrot::iterate(QPair<double, double> c0) const
{
    QPair<double, double> c = c0;
    const int imax = 255;

    int i;
    for (i=0; i<imax; ++i)
    {
        QPair<double, double> nc(c.first*c.first - c.second*c.second + c0.first, 2*c.first*c.second+c0.second);
        if (nc.first*nc.first + nc.second+nc.second > 4.0)
            break;

        c = nc;
    }
    return double(i)/double(imax);
}
