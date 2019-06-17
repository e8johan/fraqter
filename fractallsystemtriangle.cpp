#include "fractallsystemtriangle.h"

FractalLSystemTriangle::FractalLSystemTriangle(QObject *parent)
    : AbstractLSystemFractal(parent)
{
    QMap<QString, QString> rules;
    rules["F"] = "F-F+F";
    setRules(rules);
    setAxiom("F+F+F");
    setAngleStep(120);
}
