
#include "directionallight.h"

DirectionalLight::DirectionalLight()
{
    mDirection = QVector3D(0.0f, 0.0f, 0.0f);
}

DirectionalLight::DirectionalLight(QVector3D Color, float AmbientIntensity, float DiffuseIntensity, QVector3D Direction)
{
    setColor(Color);
    setAmbientIntensity(AmbientIntensity);
    setDiffuseIntensity(DiffuseIntensity);
    mDirection = Direction;
}


QVector3D DirectionalLight::getDirection()
{
    return mDirection;
}

void DirectionalLight::setDirection(QVector3D newDir)
{
    mDirection = newDir;
}
