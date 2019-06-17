#include "fractallsystemdragoncurve.h"

FractalLSystemDragonCurve::FractalLSystemDragonCurve(QObject *parent)
    : AbstractLSystemFractal(parent)
{
    QMap<QString,QString> rules;
    rules["X"] = "X+YF+";
    rules["Y"] = "-FX-Y";
    setRules(rules);
    setAxiom("FX");
    setAngleStep(90);
}
