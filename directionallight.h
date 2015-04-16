#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <QVector3D>

#include "basiclight.h"

class DirectionalLight : public BasicLight
{
public:
    DirectionalLight();
    DirectionalLight(QVector3D Color, float AmbientIntensity=0.5f, float DiffuseIntensity=0.5f, QVector3D Direction=QVector3D(0.0f, 0.0f, 0.0f));

    QVector3D getDirection();
    void setDirection(QVector3D newDir);

private:
    QVector3D mDirection;

};

#endif // DIRECTIONALLIGHT_H
