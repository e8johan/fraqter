#include "fractallsystemdragoncurve.h"

FractalLSystemDragonCurve::FractalLSystemDragonCurve(QWidget *parent)
    : AbstractLSystemView(parent)
{
    QMap<QString,QString> rules;
    rules["X"] = "X+YF+";
    rules["Y"] = "-FX-Y";
    setRules(rules);
    setAxiom("FX");
    setAngleStep(90);
}
