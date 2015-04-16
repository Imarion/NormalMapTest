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

    Vertex       *Vertices;
    unsigned int *Indices;
    DirectionalLight   mDirectionalLight;

    //debug
    void printMatrix(const QMatrix4x4& mat);
};
