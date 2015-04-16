#include "basiclight.h"

BasicLight::BasicLight()
{
    mColor            = QVector3D(0.0f, 0.0f, 0.0f);
    mAmbientIntensity = 0.0f;
    mDiffuseIntensity = 0.0f;
}

BasicLight::BasicLight(QVector3D Color, float AmbientIntensity, float DiffuseIntensity)
{
    mColor            = Color;
    mAmbientIntensity = AmbientIntensity;
    mDiffuseIntensity = DiffuseIntensity;
}

QVector3D BasicLight::getColor()
{
    return mColor;
}

float BasicLight::getAmbientIntensity()
{
    return mAmbientIntensity;
}

float BasicLight::getDiffuseIntensity()
{
    return mDiffuseIntensity;
}

void BasicLight::setColor(QVector3D newCol)
{
    mColor = newCol;
}

void BasicLight::setAmbientIntensity(float newAmbienIntensity)
{
    mAmbientIntensity = newAmbienIntensity;
}

void BasicLight::setDiffuseIntensity(float newDiffuseIntensity)
{
    mDiffuseIntensity = newDiffuseIntensity;
}
