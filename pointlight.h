#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "basiclight.h"

class PointLight : public BasicLight
{
public:
    PointLight();
    PointLight(QVector3D Color, float AmbientIntensity=0.5f, float DiffuseIntensity=0.5f, QVector3D Position=QVector3D(0.0f, 0.0f, 4.0f));

    QVector3D getPosition();
    void setPosition(QVector3D newPos);

    float getConstAtt();
    float getLinearAtt();
    float getExpAtt();

    void setConstAtt(float);
    void setLinearAtt(float);
    void setExpAtt(float);

private:
    QVector3D mPosition;

    float mConstAtt;
    float mLinearAtt;
    float mExpAtt;
};

#endif // POINTLIGHT_H
