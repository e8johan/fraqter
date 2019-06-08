#ifndef FRACTALBUDDABROT_H
#define FRACTALBUDDABROT_H

#include "abstractimaginaryrangeview.h"

class FractalBuddabrot : public AbstractImaginaryRangeView
{
    Q_OBJECT

public:
    explicit FractalBuddabrot(QWidget *parent = nullptr);

protected:
    virtual void redrawBuffer() override;
    virtual const QImage &buffer() const override;

private:
    QImage m_buffer;
};

#endif // FRACTALBUDDABROT_H
