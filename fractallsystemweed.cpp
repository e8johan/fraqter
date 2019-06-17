#include "fractallsystemweed.h"

FractalLSystemWeed::FractalLSystemWeed(QObject *parent)
    : AbstractLSystemFractal(parent)
{
    QMap<QString, QString> rules;
    rules["F"] = "FF";
    rules["X"] = "F-[[X]+X]+F[+FX]-X";
    setRules(rules);
    setAxiom("X");
    setAngleStep(22.5);
}
