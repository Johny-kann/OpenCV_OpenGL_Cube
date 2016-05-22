#include "texturemapping.h"
#include <QDebug>
#include <QScreen>
#include <QMouseEvent>

TextureMapping::TextureMapping(QWindow *parent):OpenGLWindow(parent)
{

    camera.position(0,0,-4);
    press = false;

}

TextureMapping::~TextureMapping()
{
    glDeleteTextures(1, &textureID);
       glDeleteBuffers(2, &vertexbuffer[0]);
       glDeleteBuffers(1, &index);
}

void TextureMapping::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_A: camera.addAngles(0,-1,0);
                        break;
        case Qt::Key_D: camera.addAngles(0,1,0);;
                        break;

    case Qt::Key_W: camera.addAngles(-1,0,0);
                    break;

    case Qt::Key_S: camera.addAngles(1,0,0);
                    break;

    default: break;
    }
}

void TextureMapping::mousePressEvent(QMouseEvent *event)
{
    press = true;
    last_mouse = event->pos();
}

void TextureMapping::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - last_mouse.x();
    int dy = event->y() - last_mouse.y();

    if (event->buttons() & Qt::LeftButton) {
        camera.addAngles((double)dy/40, (double)dx/40, 0);
    }
}

void TextureMapping::mouseReleaseEvent(QMouseEvent *event)
{
    press = false;
}

void TextureMapping::loadGLTexture()
{
    QImage image(":/image/Output.bmp");
    image = image.convertToFormat(QImage::Format_RGB888);
//    image = image.mirrored();

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void TextureMapping::initGeometry()
{
    glGenBuffers(2,&vertexbuffer[0]);
    glGenBuffers(1,&index);

    GLfloat vertices[] = {
        0.5f, 0.5f, -0.5f,      //Front
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        -0.5f, -0.5f,0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,      //Back

       0.5f, 0.5f, 0.5f,
       -0.5f, 0.5f, 0.5f,
       -0.5f, -0.5f,0.5f,

        -0.5f, -0.5f, -0.5f,    //Left
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,    //Right
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,     //Top

       -0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,


        -0.5f, -0.5f, -0.5f,     //Bottom
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f
    };

    GLfloat uv_data_mag[] = {

        0.75f, 0.333f,
        0.75f, 0.666f,
        1.0f, 0.666f,     //Front

        1.0f, 0.666f,
        1.0f, 0.333f,
        .75f, 0.333f,

        0.25f, 0.666f,
        0.5f, 0.666f,
        0.5f, 0.333f,

        0.5f, 0.333f,
        0.25f, 0.333f,     //Back
        0.25f, 0.666f,

        0.0f, 0.666f,     //Left
        0.25f, 0.666f,
        0.25f, 0.333f,

        0.25f, 0.333f,
        0.0f, 0.333f,
        0.0f, 0.666,

        0.5f, 0.333f,     //Right
        0.5f, 0.666f,
        0.75f, 0.666f,

        0.75f, 0.666f,
        0.75f, 0.333f,
        0.5f, 0.333,


        0.5f, 0.333f,
        0.5f, 0.0f,
        0.25f, 0.0f,

        0.25f, 0.0f,
        0.25f, 0.333f,     //Top
        0.5f, 0.333f,

        0.25f, 1.0f,
        0.5f, 1.0f,
        0.5f, 0.666f,

        0.5f, 0.666f,
        0.25f, 0.666f,     //Bottom
        0.25f, 1.0f,

    };



    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer[0]);

    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_data_mag), uv_data_mag,GL_STATIC_DRAW);


}

void TextureMapping::loadShader()
{
    m_program = new QOpenGLShaderProgram(this);
       m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/tv2.vert");
       m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/tf2.frag");
       m_program->link();
       m_posAttr = m_program->attributeLocation("posAttr");
//       m_colAttr = m_program->attributeLocation("colAttr");
       m_texCoordAttr = m_program->attributeLocation("texCoordAttr");
       m_matrixUniform = m_program->uniformLocation("mvpMatrix");
       m_textureUniform = m_program->uniformLocation("texture");

       qDebug()<<m_posAttr<<m_colAttr<<m_texCoordAttr<<m_matrixUniform<<m_textureUniform;
}


void TextureMapping::initialize()
{

    initGeometry();
    loadGLTexture();
    loadShader();


    glEnable(GL_CULL_FACE);

    glShadeModel(GL_SMOOTH);

    glDepthFunc(GL_LESS);
//    glDepthMask(GL_TRUE);
    glEnable(GL_TEXTURE_2D);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

}

void TextureMapping::render()
{

    static int angle = 0;

    const qreal retinaScale = devicePixelRatio();
        glViewport(0, 0, width() * retinaScale, height() * retinaScale);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);

        glDepthFunc(GL_LESS);

        m_program->bind();

        QMatrix4x4 matrix, perspective, cam_matrix;

        matrix.setToIdentity();
        perspective.setToIdentity();
        cam_matrix.setToIdentity();

        cam_matrix.translate(camera.position_axis);

        perspective.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);

        matrix.translate(0, 0, 0);

        cam_matrix.rotate(camera.angle.x()*2, 1, 0, 0);
        cam_matrix.rotate(camera.angle.y()*2, 0, 1, 0);
        cam_matrix.rotate(camera.angle.z()*2, 0, 0, 1);

        if(!press)
        {
        matrix.rotate(angle, 0,1,0);

        angle+=2;
        if(angle>360)
            angle %= 360;
        }


        m_program->setUniformValue(m_matrixUniform, perspective*cam_matrix*matrix);

        glActiveTexture(GL_TEXTURE0);

         glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);

        glEnableVertexAttribArray(m_posAttr);

        glVertexAttribPointer(m_posAttr,3,GL_FLOAT,GL_FALSE,0,(void*)0);


        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);

        glEnableVertexAttribArray(m_texCoordAttr);
        glVertexAttribPointer(m_texCoordAttr, 2, GL_FLOAT, GL_FALSE,0,(void*)0);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glDrawArrays(GL_TRIANGLES, 0, 3*2*6);
        glDisableVertexAttribArray(m_texCoordAttr);
        glDisableVertexAttribArray(m_posAttr);


        m_program->release();

        ++m_frame;
}
