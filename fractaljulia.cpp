#include "fractaljulia.h"

FractalJulia::FractalJulia(QWidget *parent) : AbstractImaginaryRangeView(parent)
{

}

double FractalJulia::iterate(QPair<double, double> z0) const
{
    const QPair<double, double> c(-0.8, 0.156);
    QPair<double, double> z = z0;
    const int imax = 500;

    int i;
    for (i=0; i<imax; ++i)
    {
        QPair<double, double> nz(z.first*z.first-z.second*z.second+c.first, 2*z.first*z.second+c.second);
        if (nz.first*nz.first + nz.second+nz.second > 4.0)
            break;

        z = nz;
    }
    return double(i)/double(imax);
}
