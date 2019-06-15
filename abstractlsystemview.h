#ifndef ABSTRACTLSYSTEMVIEW_H
#define ABSTRACTLSYSTEMVIEW_H

#include "abstractfractalview.h"

#include <QMap>

class AbstractLSystemView : public AbstractFractalView
{
    Q_OBJECT

    Q_PROPERTY(int iterations READ iterations WRITE setIterations NOTIFY iterationsChanged)

public:
    explicit AbstractLSystemView(QWidget *parent = nullptr);

    int iterations() const;

public slots:
    void setIterations(int iterations);

signals:
    void iterationsChanged(int iterations);

protected:
    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;

    virtual void forceRedraw() override;

    /*
     * For L-Systems, we separate the calculation of the line segments from the drawing of them.
     * This allows us to resize without having to recalculate the line segments.
     */
    void redrawBuffer();
    void recalculateLines();

    QString axiom() const;
    QString fromRule(const QChar &) const;
    qreal angleStep() const;

    void setAxiom(const QString &);
    void setRules(const QMap<QString, QString> &);
    void setAngleStep(qreal);

private:
    QString m_axiom;
    QMap<QString, QString> m_rules;
    qreal m_angleStep;
    QImage m_buffer;
    QList<QLineF> m_lines;
    int m_iterations;
    bool m_linesDirty;
};

#endif // ABSTRACTLSYSTEMVIEW_H
