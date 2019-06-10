#ifndef ABSTRACTIMAGINARYRANGEESCAPEVIEW_H
#define ABSTRACTIMAGINARYRANGEESCAPEVIEW_H

#include "abstractimaginaryrangeview.h"

class AbstractImaginaryRangeEscapeView : public AbstractImaginaryRangeView
{
    Q_OBJECT

    Q_PROPERTY(int maxIterations READ maxIterations WRITE setMaxIterations NOTIFY maxIterationsChanged)

public:
    explicit AbstractImaginaryRangeEscapeView(QWidget *parent = nullptr);

    int maxIterations() const;

public slots:
    void setMaxIterations(int maxIterations);
    virtual void forceRedraw() override;

signals:
    void maxIterationsChanged(int maxIterations);

protected:
    virtual void redrawBuffer() override;
    virtual const QImage &buffer() const override;

    virtual double iterate(const FComplex &) const = 0;

private:
    QImage m_buffer;

    int m_maxIterations;
};

#endif // ABSTRACTIMAGINARYRANGEESCAPEVIEW_H
