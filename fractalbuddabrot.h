#ifndef FRACTALBUDDABROT_H
#define FRACTALBUDDABROT_H

#include "abstractimaginaryrangeview.h"

class FractalBuddabrot : public AbstractImaginaryRangeView
{
    Q_OBJECT

    Q_PROPERTY(qreal iterationsFactor READ iterationsFactor WRITE setIterationsFactor NOTIFY iterationsFactorChanged)
    Q_PROPERTY(int maxIterations READ maxIterations WRITE setMaxIterations NOTIFY maxIterationsChanged)

public:
    explicit FractalBuddabrot(QWidget *parent = nullptr);

    qreal iterationsFactor() const;
    int maxIterations() const;

public slots:
    virtual void forceRedraw() override;

    void setIterationsFactor(qreal iterationsFactor);
    void setMaxIterations(int maxIterations);

signals:
    void iterationsFactorChanged(qreal iterationsFactor);
    void maxIterationsChanged(int maxIterations);

protected:
    virtual void redrawBuffer() override;
    virtual const QImage &buffer() const override;

private:
    QImage m_buffer;
    qreal m_iterationsFactor;
    int m_maxIterations;
};

#endif // FRACTALBUDDABROT_H
