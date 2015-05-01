#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <QVector3D>

#include "basiclight.h"

class DirectionalLight : public BasicLight
{
public:
    DirectionalLight();
    DirectionalLight(QVector3D Color, float AmbientIntensity=0.5f, float DiffuseIntensity=0.5f, QVector3D DirPos=QVector3D(0.0f, 0.0f, 0.0f));

    QVector3D getDirPos();
    void setDirPos(QVector3D newDirPos);

private:
    QVector3D mDirPos;
};

#endif // DIRECTIONALLIGHT_H
