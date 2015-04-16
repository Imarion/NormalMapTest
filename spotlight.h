#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <QVector3D>

#include "pointlight.h"

class SpotLight : public PointLight
{
public:
    SpotLight();

    void setDirection(QVector3D newDir);
    void setCutoff(float newCutoff);

    QVector3D getDirection();
    float     getCutoff();

private:
    QVector3D mDirection;
    float     mCutoff;
};

#endif // SPOTLIGHT_H
