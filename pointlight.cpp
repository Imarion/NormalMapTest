#include "pointlight.h"

PointLight::PointLight()
{
    mPosition  = QVector3D(0.0f, 0.0f, 0.0f);
    mConstAtt  = 1.0f;
    mLinearAtt = 0.0f;
    mExpAtt    = 0.0f;
}

PointLight::PointLight(QVector3D Color, float AmbientIntensity, float DiffuseIntensity, QVector3D Position)
{
    setColor(Color);
    setAmbientIntensity(AmbientIntensity);
    setDiffuseIntensity(DiffuseIntensity);
    mPosition = Position;
}

QVector3D PointLight::getPosition()
{
    return mPosition;
}

void PointLight::setPosition(QVector3D newPos)
{
    mPosition = newPos;
}

float PointLight::getConstAtt()
{
    return mConstAtt;
}

float PointLight::getLinearAtt()
{
    return mLinearAtt;
}

float PointLight::getExpAtt()
{
    return mExpAtt;
}

void PointLight::setConstAtt(float newAtt)
{
    mConstAtt = newAtt;
}

void PointLight::setLinearAtt(float newAtt)
{
    mLinearAtt = newAtt;
}

void PointLight::setExpAtt(float newAtt)
{
    mExpAtt = newAtt;
}


