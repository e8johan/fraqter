#ifndef ABSTRACTIMAGINARYRANGEVIEW_H
#define ABSTRACTIMAGINARYRANGEVIEW_H

#include "abstractfractalview.h"

class AbstractImaginaryRangeView : public AbstractFractalView
{
public:
    explicit AbstractImaginaryRangeView(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);

    virtual double iterate(QPair<double, double>) const = 0;

private:
    QImage m_buffer;
};

#endif // ABSTRACTIMAGINARYRANGEVIEW_H
