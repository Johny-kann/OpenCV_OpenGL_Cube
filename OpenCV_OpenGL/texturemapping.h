#ifndef TEXTUREMAPPING_H
#define TEXTUREMAPPING_H

#include "openglwindow.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QList>
#include <QVector2D>
#include "camera.h"

struct VertexData
{
    QVector3D position;
    QVector3D normal;
    QVector2D texCoord;
};



class TextureMapping : public OpenGLWindow
{
    Q_OBJECT
public:
    TextureMapping(QWindow *parent = 0);
    ~TextureMapping();

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;
    void initGeometry();
    void loadGLTexture();
    void loadShader();

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_texCoordAttr;
    GLuint m_matrixUniform;
    GLuint m_textureUniform;

    QOpenGLShaderProgram *m_program;
    GLuint vertexbuffer[2];
    GLuint textureID;
    GLuint index;
    int m_frame;
    QPoint last_mouse;
    bool press;

    Camera camera;

};


#endif // TEXTUREMAPPING_H
