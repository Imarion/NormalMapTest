
#include <QVector3D>

#include "spotlight.h"

SpotLight::SpotLight()
{
    mDirection = QVector3D(0.0f, 0.0f, 0.0f);
    mCutoff    = 0.0f;
}

void SpotLight::setDirection(QVector3D newDir)
{
    mDirection = newDir;
}

void SpotLight::setCutoff(float newCutoff)
{
    mCutoff = newCutoff;
}

QVector3D SpotLight::getDirection()
{
    return mDirection;
}

float SpotLight::getCutoff()
{
    return mCutoff;
}
