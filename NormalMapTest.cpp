#include "NormalMapTest.h"

#include <QDebug>
#include <QFile>
#include <QImage>

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>

#include <cmath>

#include "utils.h"
#include "vertex.h"

#define NUM_VERTICES    36
#define NUM_INDICES     36
//#define NUM_VERTICES    4
//#define NUM_INDICES     6


MyWindow::~MyWindow()
{
    if (Vertices != 0) delete[] Vertices;
    if (Indices  != 0) delete[] Indices;
}

MyWindow::MyWindow() : currentTimeMs(0), currentTimeS(0)
{
    Vertices = 0;
    Indices  = 0;

    setSurfaceType(QWindow::OpenGLSurface);
    setFlags(Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
    create();

    resize(800, 600);

    mContext = new QOpenGLContext(this);
    mContext->setFormat(format);
    mContext->create();

    mContext->makeCurrent( this );

    mFuncs = mContext->versionFunctions<QOpenGLFunctions_3_3_Core>();
    if ( !mFuncs )
    {
        qWarning( "Could not obtain OpenGL versions object" );
        exit( 1 );
    }
    if (mFuncs->initializeOpenGLFunctions() == GL_FALSE)
    {
        qWarning( "Could not initialize core open GL functions" );
        exit( 1 );
    }

    initializeOpenGLFunctions();

    QTimer *repaintTimer = new QTimer(this);
    connect(repaintTimer, &QTimer::timeout, this, &MyWindow::render);
    repaintTimer->start(1000/60);

    QTimer *elapsedTimer = new QTimer(this);
    connect(elapsedTimer, &QTimer::timeout, this, &MyWindow::modCurTime);
    elapsedTimer->start(1);       
}

void MyWindow::modCurTime()
{
    currentTimeMs++;
    currentTimeS=currentTimeMs/1000.0f;
}

void MyWindow::initialize()
{
    mFuncs->glGenVertexArrays(1, &mVAO);
    mFuncs->glBindVertexArray(mVAO);

    CreateVertexBuffer();
    initShaders();

    //mDirectionalLight.setColor(QVector3D(1.0f, 1.0f, 1.0f)); // tut 19
    mDirectionalLight.setColor(QVector3D(1.0f, 1.0f, 1.0f));   // tut 20
    mDirectionalLight.setAmbientIntensity(1.0f);
    mDirectionalLight.setDiffuseIntensity(1.0f);
    mDirectionalLight.setDirection(QVector3D(0.0f, 0.0f, 1.0f));

    gWVPLocation     = mProgram->uniformLocation("gWVP");
    gWorldLocation   = mProgram->uniformLocation("gWorld");
    gSamplerLocation = mProgram->uniformLocation("gSampler");
    glUniform1i(gSamplerLocation, 0);

    mDirLightColorLocation            = mProgram->uniformLocation("gDirectionalLight.Base.Color");
    mDirLightAmbientIntensityLocation = mProgram->uniformLocation("gDirectionalLight.Base.AmbientIntensity");
    mDirLightDiffuseIntensityLocation = mProgram->uniformLocation("gDirectionalLight.Base.DiffuseIntensity");
    mDirLightDirectionLocation        = mProgram->uniformLocation("gDirectionalLight.Direction");

    // for Specular (tut19)
    mEyeWorldPosLocation            = mProgram->uniformLocation("EyeWorldPos");
    mMatSpecularIntensityLocation   = mProgram->uniformLocation("gMatProp.SpecularIntensity");
    mMatSpecularPowerLocation       = mProgram->uniformLocation("gMatProp.SpecularPower");

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    PrepareTexture(GL_TEXTURE_2D, "F:/Download/Programmation/OpenGL/ogldev-source/ogldev-source/tutorial16/test.png");
    //PrepareTexture(GL_TEXTURE_2D, "C:/Users/emr/Documents/Perso/Programmation/Opengl/Ogldev/ogldev-source/tutorial19/test.png");
}

void MyWindow::CreateVertexBuffer()
{
    // C++11 required
    Vertices = new VertexTex[NUM_VERTICES] {
        // front
        VertexTex(QVector3D(-1.0f,  1.0f, 1.0f),  QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D(-1.0f, -1.0f, 1.0f),  QVector2D(0.0f, 0.0f)), // lower left
        VertexTex(QVector3D( 1.0f, -1.0f, 1.0f),  QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D(-1.0f,  1.0f, 1.0f),  QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D( 1.0f, -1.0f, 1.0f),  QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D( 1.0f,  1.0f, 1.0f),  QVector2D(1.0f, 1.0f)), // upper right

        // left
        VertexTex(QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)), // lower left
        VertexTex(QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 1.0f)), // upper right

        // right
        VertexTex(QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)), // lower left
        VertexTex(QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)), // upper right

        // back
        VertexTex(QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)), // lower left
        VertexTex(QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)), // upper right

        // top
        VertexTex(QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.0f, 0.0f)), // lower left
        VertexTex(QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 1.0f)), // upper right

        // bottom
        VertexTex(QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)), // lower left
        VertexTex(QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 1.0f)), // upper left
        VertexTex(QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)), // lower right
        VertexTex(QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(1.0f, 1.0f)), // upper right

/*
        VertexTex(QVector3D(-1.0f, -1.0f, 0.0f),  QVector2D(0.0f, 0.0f)), // 0 lower left front
        VertexTex(QVector3D( 1.0f, -1.0f, 0.0f),  QVector2D(1.0f, 0.0f)), // 1 lower right front
        VertexTex(QVector3D(-1.0f,  1.0f, 0.0f),  QVector2D(0.0f, 1.0f)), // 2 upper left front
        VertexTex(QVector3D( 1.0f,  1.0f, 0.0f),  QVector2D(1.0f, 1.0f)), // 3 upper right front
        VertexTex(QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.0f)), // 4 lower left back (=lower right when looking at ...)
        VertexTex(QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)), // 5 lower right back
        VertexTex(QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)), // 6 upper left back
        VertexTex(QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.0f, 1.0f)), // 7 upper right back
*/
    };
    Indices = new unsigned int[NUM_INDICES] {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
    };
    /*
    Indices = new unsigned int[NUM_INDICES] {
         0, 2, 3,
         0, 1, 2
    };
    */

    utils::CalcNormals(Indices, NUM_INDICES, Vertices, NUM_VERTICES);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0])*NUM_VERTICES, Vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0])*NUM_INDICES, Indices, GL_STATIC_DRAW);
}

void MyWindow::resizeEvent(QResizeEvent *)
{
    mUpdateSize = true;
}

void MyWindow::render()
{
    if(!isVisible() || !isExposed())
        return;

    if (!mContext->makeCurrent(this))
        return;

    static bool initialized = false;
    if (!initialized) {
        initialize();
        initialized = true;
    }

    if (mUpdateSize) {
        glViewport(0, 0, size().width(), size().height());
        mUpdateSize = false;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTex), 0);    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTex), (const GLvoid*)(sizeof(Vertices[0].getPos())));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTex), (const GLvoid*)((sizeof(Vertices[0].getPos()))+(sizeof(Vertices[0].getNormal()))));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureObject);

    static float Scale = 0.0f;
    Scale += 0.1f; // tut 12

    QMatrix4x4 WVP, World;
    QVector3D  CameraPos(0.0f, 0.0f, 5.0f);

    //World.translate(0.0f, 0.0f, 1.0f);
    //World.translate(0.0f, 0.0f, Scale/10.0f);
    World.rotate(Scale*2, 1.0f, 0.0f, 0.0f);
    //mPointLight.setPosition(mPointLight.getPosition()-QVector3D(0.0f, 0.0f, Scale/1000.0f));

    WVP.perspective(60.0f, (float)this->width()/(float)this->height(), 1.0f, 100.0f);
    WVP.lookAt(CameraPos, QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));

    WVP *= World;

    mProgram->bind();
    {
        glUniformMatrix4fv(gWVPLocation, 1, GL_FALSE, WVP.constData());
        glUniformMatrix4fv(gWorldLocation, 1, GL_FALSE, World.constData());        

        glUniform3f(mDirLightColorLocation,mDirectionalLight.getColor().x(), mDirectionalLight.getColor().y(), mDirectionalLight.getColor().z());
        glUniform1f(mDirLightAmbientIntensityLocation, mDirectionalLight.getAmbientIntensity());
        QVector3D Direction = mDirectionalLight.getDirection();
        Direction.normalize();
        glUniform3f(mDirLightDirectionLocation, Direction.x(), Direction.y(), Direction.z());
        glUniform1f(mDirLightDiffuseIntensityLocation, mDirectionalLight.getDiffuseIntensity());

        // for specular, tut 19
        glUniform3f(mEyeWorldPosLocation, CameraPos.x(), CameraPos.y(), CameraPos.z());
        //glUniform1f(mMatSpecularIntensityLocation, 1.0f);
        //glUniform1f(mMatSpecularPowerLocation, 32.0f);
        // tut 20 -> specular 0
        glUniform1f(mMatSpecularIntensityLocation, 0.0f);
        glUniform1f(mMatSpecularPowerLocation, 0.0f);

        glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }
    mProgram->release();

    mContext->swapBuffers(this);
}

void MyWindow::initShaders()
{
    QOpenGLShader vShader(QOpenGLShader::Vertex);
    QOpenGLShader fShader(QOpenGLShader::Fragment);
    QFile         shaderFile;
    QByteArray    shaderSource;

    //mProgram
    // Shader 1
    shaderFile.setFileName(":/vshader_texture.txt");
    shaderFile.open(QIODevice::ReadOnly);
    shaderSource = shaderFile.readAll();
    shaderFile.close();
    qDebug() << "vertex 1 compile: " << vShader.compileSourceCode(shaderSource);

    shaderFile.setFileName(":/fshader_texture.txt");
    shaderFile.open(QIODevice::ReadOnly);
    shaderSource = shaderFile.readAll();
    shaderFile.close();
    qDebug() << "frag   1 compile: " << fShader.compileSourceCode(shaderSource);

    mProgram = new (QOpenGLShaderProgram);
    mProgram->addShader(&vShader);
    mProgram->addShader(&fShader);
    qDebug() << "shader link: " << mProgram->link();
}

void MyWindow::PrepareTexture(GLenum TextureTarget, const QString& FileName)
{
    QImage TexImg;

    if (!TexImg.load(FileName)) qDebug() << "Erreur chargement texture";
    glGenTextures(1, &mTextureObject);
    glBindTexture(TextureTarget, mTextureObject);
    glTexImage2D(TextureTarget, 0, GL_RGB, TexImg.width(), TexImg.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, TexImg.bits());
    glTexParameterf(TextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(TextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void MyWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_P:
            break;
        case Qt::Key_Up:
            break;
        case Qt::Key_Down:
            break;
        case Qt::Key_Left:
            break;
        case Qt::Key_Right:
            break;
        case Qt::Key_Delete:
            break;
        case Qt::Key_PageDown:
            break;
        case Qt::Key_Home:
            break;
        case Qt::Key_Z:
            break;
        case Qt::Key_Q:
            break;
        case Qt::Key_S:
            break;
        case Qt::Key_D:
            break;
        case Qt::Key_X:
            break;
        case Qt::Key_W:
            break;
        default:
            break;
    }
}


void MyWindow::printMatrix(const QMatrix4x4& mat)
{
    const float *locMat = mat.transposed().constData();

    for (int i=0; i<4; i++)
    {
        qDebug() << locMat[i*4] << " " << locMat[i*4+1] << " " << locMat[i*4+2] << " " << locMat[i*4+3];
    }
}
