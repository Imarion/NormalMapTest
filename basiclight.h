#ifndef BASICLIGHT_H
#define BASICLIGHT_H

#include <QVector3D>

class BasicLight
{
public:
    BasicLight();
    BasicLight(QVector3D Color, float AmbientIntensity=0.5f, float DiffuseIntensity=0.5f);

private:
    QVector3D mColor;
    float     mAmbientIntensity;
    float     mDiffuseIntensity;

public:
    QVector3D getColor();
    float     getAmbientIntensity();
    float     getDiffuseIntensity();

    void setColor(QVector3D newCol);
    void setAmbientIntensity(float newAmbienIntensity);
    void setDiffuseIntensity(float newDiffuseIntensity);
};

#endif // BASICLIGHT_H
