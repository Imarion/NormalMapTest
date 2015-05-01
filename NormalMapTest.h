#include <QWindow>
#include <QTimer>
#include <QString>
#include <QKeyEvent>

#include <QVector3D>

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLShaderProgram>

#include "vertextex.h"
#include "directionallight.h"

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

    void PrepareTexture(GLenum TextureTarget, const QString& FileName, GLuint& TexObject);

protected:
    void resizeEvent(QResizeEvent *);

private:
    QOpenGLContext *mContext;
    QOpenGLFunctions_3_3_Core *mFuncs;

    enum ProgramType
    {
        SIMPLE_TEX,
        NORMAL_MAP
    } mPtype;
    QOpenGLShaderProgram *mProgram[2]; // 0 = no normal map, 1 = normal map

    QTimer mRepaintTimer;
    double currentTimeMs;
    double currentTimeS;
    bool   mUpdateSize;

    GLuint mVAO, mVBO, mIBO;
    GLuint mTextureObject, mNormalTexObject;

    GLuint gCameraLocation[2], gModelLocation[2], gSamplerLocation[2], gNormalSamplerLocation;
    GLuint mDirLightColorLocation[2], mDirLightAmbientIntensityLocation[2];
    GLuint mDirLightPositionLocation[2], mDirLightDiffuseIntensityLocation[2];
    GLuint mEyeWorldPosLocation[2];
    GLuint mMatSpecularIntensityLocation[2], mMatSpecularPowerLocation[2];

    VertexTex    *Vertices;
    unsigned int *Indices;
    DirectionalLight   mDirectionalLight;

    //debug
    void printMatrix(const QMatrix4x4& mat);
};
