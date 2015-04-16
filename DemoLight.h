#include <QWindow>
#include <QTimer>
#include <QString>
#include <QKeyEvent>

#include <QVector3D>

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLShaderProgram>

#include "vertex.h"
#include "directionallight.h"
#include "pointlight.h"
#include "spotlight.h"

#define ToRadian(x) ((x) * M_PI / 180.0f)
#define ToDegree(x) ((x) * 180.0f / M_PI)

//class MyWindow : public QWindow, protected QOpenGLFunctions_3_3_Core
class MyWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit MyWindow();
    ~MyWindow();
    virtual void keyPressEvent( QKeyEvent *keyEvent );    

private slots:
    void render();

private:    
    void initialize();
    void modCurTime();

    void initShaders();
    void CreateVertexBuffer();

    void PrepareTexture(GLenum TextureTarget, const QString& FileName);

protected:
    void resizeEvent(QResizeEvent *);

private:
    QOpenGLContext *mContext;
    QOpenGLFunctions_3_3_Core *mFuncs;

    QOpenGLShaderProgram *mProgram;

    QTimer mRepaintTimer;
    double currentTimeMs;
    double currentTimeS;
    bool   mUpdateSize;

    GLuint mVAO, mVBO, mIBO;
    GLuint mTextureObject;

    GLuint gWVPLocation, gWorldLocation, gSamplerLocation;
    GLuint mDirLightColorLocation, mDirLightAmbientIntensityLocation;
    GLuint mDirLightDirectionLocation, mDirLightDiffuseIntensityLocation;
    GLuint mEyeWorldPosLocation;
    GLuint mMatSpecularIntensityLocation, mMatSpecularPowerLocation;

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        struct
        {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } mPointLightsLocation[1];

    struct {
        GLuint Color;
        GLuint AmbientIntensity;
        GLuint DiffuseIntensity;
        GLuint Position;
        GLuint Direction;
        GLuint Cutoff;
        struct {
            GLuint Constant;
            GLuint Linear;
            GLuint Exp;
        } Atten;
    } mSpotLightsLocation[1];

    Vertex       *Vertices;
    unsigned int *Indices;
    DirectionalLight   mDirectionalLight;
    PointLight         mPointLight;
    SpotLight          mSpotLight;

    //debug
    void printMatrix(const QMatrix4x4& mat);
};
