#include "fractallsystemtriangle.h"

FractalLSystemTriangle::FractalLSystemTriangle(QWidget *parent)
    : AbstractLSystemView(parent)
{
    QMap<QString, QString> rules;
    rules["F"] = "F-F+F";
    setRules(rules);
    setAxiom("F+F+F");
    setAngleStep(120);
}
