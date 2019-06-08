#include "abstractimaginaryrangeescapeview.h"

AbstractImaginaryRangeEscapeView::AbstractImaginaryRangeEscapeView(QWidget *parent)
    : AbstractImaginaryRangeView(parent)
    , m_maxIterations(1000)
{

}

int AbstractImaginaryRangeEscapeView::maxIterations() const
{
    return m_maxIterations;
}

void AbstractImaginaryRangeEscapeView::setMaxIterations(int maxIterations)
{
    if (m_maxIterations == maxIterations)
        return;

    m_maxIterations = maxIterations;
    redrawBuffer();
    emit maxIterationsChanged(m_maxIterations);
}

const QImage &AbstractImaginaryRangeEscapeView::buffer() const
{
    return m_buffer;
}

void AbstractImaginaryRangeEscapeView::redrawBuffer()
{
    m_buffer = QImage(size(), QImage::Format_ARGB32);

    for (int x=0; x<m_buffer.width(); ++x)
        for (int y=0; y<m_buffer.height(); ++y)
        {
            FComplex coord(double(x)/double(m_buffer.width())*(bottomRightCoord().real-topLeftCoord().real)+topLeftCoord().real,
                           double(y)/double(m_buffer.height())*(bottomRightCoord().imag-topLeftCoord().imag)+topLeftCoord().imag);
            double f = iterate(coord);
            QColor color = QColor(0, 0, 0);
            if (f < 255.0 / 256.0)
                color = QColor(int(f*255), int(f*255), int((1.0-f)*64));
            m_buffer.setPixelColor(x, y, color);
        }

    update();
}
