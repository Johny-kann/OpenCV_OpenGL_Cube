#ifndef OPENGLWINDOWN_H
#define OPENGLWINDOWN_H

#include <QWindow>
#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>
#include <QTimer>

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

    public:
       explicit OpenGLWindow(QWindow *parent = 0);
       ~OpenGLWindow();

//       virtual void render(QPainter *painter);
       virtual void render();

       virtual void initialize();

       void setAnimating(bool animating);

   public slots:
       void renderLater();
       void renderNow();
       void updateFrame();

   protected:
       bool event(QEvent *event) Q_DECL_OVERRIDE;

       void exposeEvent(QExposeEvent *event) Q_DECL_OVERRIDE;

   private:
       bool m_update_pending;
       bool m_animating;
       QTimer *timer;

       QOpenGLContext *m_context;
       QOpenGLPaintDevice *m_device;
};

#endif // OPENGLWINDOWN_H
