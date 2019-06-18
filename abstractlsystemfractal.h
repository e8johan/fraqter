#ifndef ABSTRACTLSYSTEMFRACTAL_H
#define ABSTRACTLSYSTEMFRACTAL_H

#include "abstractfractal.h"

#include <QMap>

class AbstractLSystemFractal : public AbstractFractal
{
    Q_OBJECT

    Q_PROPERTY(int iterations READ iterations WRITE setIterations NOTIFY iterationsChanged)

public:
    explicit AbstractLSystemFractal(QObject *parent = nullptr);

    virtual bool canZoom() const override;

    virtual void generateNewBuffer(const QSize &) override;

    int iterations() const;

public slots:
    void setIterations(int iterations);

signals:
    void iterationsChanged(int iterations);

protected:
    /*
     * For L-Systems, we separate the calculation of the line segments from the drawing of them.
     * This allows us to resize without having to recalculate the line segments.
     */
    void redrawBuffer(const QSize &);
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

    QList<QLineF> m_lines;
    int m_iterations;
    bool m_linesDirty;
};

#endif // ABSTRACTLSYSTEMFRACTAL_H
