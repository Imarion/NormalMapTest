
#include "directionallight.h"

DirectionalLight::DirectionalLight()
{
    mDirPos = QVector3D(0.0f, 0.0f, 0.0f);
}

DirectionalLight::DirectionalLight(QVector3D Color, float AmbientIntensity, float DiffuseIntensity, QVector3D DirPos)
{
    setColor(Color);
    setAmbientIntensity(AmbientIntensity);
    setDiffuseIntensity(DiffuseIntensity);
    mDirPos = DirPos;
}


QVector3D DirectionalLight::getDirPos()
{
    return mDirPos;
}

void DirectionalLight::setDirPos(QVector3D newDirPos)
{
    mDirPos = newDirPos;
}

