#ifndef ABSTRACTFRACTALVIEW_H
#define ABSTRACTFRACTALVIEW_H

#include <QWidget>
#include <QImage>

class AbstractFractalView : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractFractalView(QWidget *parent = nullptr);
};

#endif // ABSTRACTFRACTALVIEW_H
