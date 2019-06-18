#include "abstractlsystemfractal.h"

#include <QPainter>
#include <QPaintEvent>
#include <QStringBuilder>

#include <math.h>

AbstractLSystemFractal::AbstractLSystemFractal(QObject *parent)
    : AbstractFractal(parent)
    , m_angleStep(0)
    , m_iterations(3)
    , m_linesDirty(true)
{
}

bool AbstractLSystemFractal::canZoom() const
{
    return false;
}

int AbstractLSystemFractal::iterations() const
{
    return m_iterations;
}

void AbstractLSystemFractal::setIterations(int iterations)
{
    if (m_iterations == iterations)
        return;

    m_iterations = iterations;

    m_linesDirty = true;
    emit bufferNeedsRepaint();

    emit iterationsChanged(m_iterations);
}

void AbstractLSystemFractal::generateNewBuffer(const QSize &size)
{
    if (m_linesDirty)
        recalculateLines();

    redrawBuffer(size);
}

void AbstractLSystemFractal::redrawBuffer(const QSize &size)
{
    QImage buffer = QImage(size, QImage::Format_ARGB32);
    buffer.fill(Qt::white);

    if (m_lines.length() > 0)
    {
        qreal minX, minY, maxX, maxY;

        minX = maxX = m_lines.first().p1().x();
        minY = maxY = m_lines.first().p1().y();

        for (QList<QLineF>::ConstIterator ii = m_lines.constBegin(); ii != m_lines.constEnd(); ++ii)
        {
            QPointF p = ii->p1();
            bool quit = false;

            while (1)
            {
                if (p.x() < minX)
                    minX = p.x();
                if (p.x() > maxX)
                    maxX = p.x();
                if (p.y() < minY)
                    minY = p.y();
                if (p.y() > maxY)
                    maxY = p.y();

                if (quit)
                    break;
                else
                {
                    p = ii->p2();
                    quit = true;
                }
            }
        }

        qreal linesWidth = (maxX - minX);
        qreal linesHeight = (maxY - minY);

        qreal factor = buffer.width()/linesWidth;
        if (buffer.height()/linesHeight < factor)
            factor = buffer.height()/linesHeight;

        factor *= 0.9; // Adding 10% margin

        qreal xOffset = (buffer.width()-linesWidth*factor)/2.0;
        qreal yOffset = (buffer.height()-linesHeight*factor)/2.0;

        QPainter p(&buffer);
        p.setPen(Qt::black);

        for (QList<QLineF>::ConstIterator ii = m_lines.constBegin(); ii != m_lines.constEnd(); ++ii)
        {
            p.drawLine(QLineF((ii->p1().x()-minX)*factor+xOffset, buffer.height()-(ii->p1().y()-minY)*factor-yOffset,
                       (ii->p2().x()-minX)*factor+xOffset, buffer.height()-(ii->p2().y()-minY)*factor-yOffset));
        }
    }
    else
        qDebug("LSystem: no lines generated");

    setBuffer(buffer);
}

void AbstractLSystemFractal::recalculateLines()
{
    QString string = axiom();

    int i = m_iterations;
    while(i-- > 0)
    {
        QString nextString;
        for (QString::ConstIterator ii = string.constBegin(); ii != string.constEnd(); ++ii)
        {
            nextString = nextString % fromRule(*ii);
        }
        string = nextString;
    }

    /*
        Inspiration from http://paulbourke.net/fractals/lsys/

        F	         Move forward by line length drawing a line
        f	         Move forward by line length without drawing a line
        +	         Turn left by turning angle
        -	         Turn right by turning angle
        |	         Reverse direction (ie: turn by 180 degrees) [NOT IMPLEMENTED]
        [	         Push current drawing state onto stack
        ]	         Pop current drawing state from the stack
        #	         Increment the line width by line width increment [NOT IMPLEMENTED]
        !	         Decrement the line width by line width increment [NOT IMPLEMENTED]
        @	         Draw a dot with line width radius [NOT IMPLEMENTED]
        {	         Open a polygon [NOT IMPLEMENTED]
        }	         Close a polygon and fill it with fill colour [NOT IMPLEMENTED]
        >	         Multiply the line length by the line length scale factor [NOT IMPLEMENTED]
        <	         Divide the line length by the line length scale factor [NOT IMPLEMENTED]
        &	         Swap the meaning of + and - [NOT IMPLEMENTED]
        (	         Decrement turning angle by turning angle increment [NOT IMPLEMENTED]
        )	         Increment turning angle by turning angle increment [NOT IMPLEMENTED]
   */

    qreal angleStep = AbstractLSystemFractal::angleStep();

    // Draw state
    qreal lineLength = 10;
    qreal angle = 0;
    qreal posx = 0, posy = 0;

    // Draw state stack
    QList<qreal> stateStack;

    m_lines.clear();

    for (QString::ConstIterator ii = string.constBegin(); ii != string.constEnd(); ++ii)
    {
        if (*ii == "F")
        {
            qreal nextPosx = posx + sin(angle/180.0*M_PI)*lineLength;
            qreal nextPosy = posy + cos(angle/180.0*M_PI)*lineLength;

            m_lines.append(QLineF(posx, posy, nextPosx, nextPosy));

            posx = nextPosx;
            posy = nextPosy;
        }
        else if (*ii == "f")
        {
            posx += sin(angle/180.0*M_PI)*lineLength;
            posy += cos(angle/180.0*M_PI)*lineLength;
        }
        else if (*ii == "+")
        {
            angle -= angleStep;
        }
        else if (*ii == "-")
        {
            angle += angleStep;
        }
        else if (*ii == "[")
        {
            stateStack.append(lineLength);
            stateStack.append(angle);
            stateStack.append(posx);
            stateStack.append(posy);
        }
        else if (*ii == "]")
        {
            if (stateStack.length() < 4)
                qWarning("LSystem: trying to pop from an empty stack");
            {
                posy = stateStack.takeLast();
                posx = stateStack.takeLast();
                angle = stateStack.takeLast();
                lineLength = stateStack.takeLast();
            }
        }
    }

    m_linesDirty = false;
}

QString AbstractLSystemFractal::axiom() const
{
    return m_axiom;
}

QString AbstractLSystemFractal::fromRule(const QChar &c) const
{
    QMap<QString,QString>::ConstIterator ii = m_rules.find(c);
    if (ii != m_rules.end())
        return ii.value();
    else
        return QString(c);
}

qreal AbstractLSystemFractal::angleStep() const
{
    return m_angleStep;
}

void AbstractLSystemFractal::setAxiom(const QString &a)
{
    m_axiom = a;
}

void AbstractLSystemFractal::setRules(const QMap<QString, QString> &r)
{
    m_rules = r;
}

void AbstractLSystemFractal::setAngleStep(qreal a)
{
    m_angleStep = a;
}
