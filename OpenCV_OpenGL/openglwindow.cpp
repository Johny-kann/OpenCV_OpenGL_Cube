#include "openglwindow.h"
#include <QCoreApplication>

OpenGLWindow::OpenGLWindow(QWindow *parent)
    : QWindow(parent)
    , m_update_pending(false)
    , m_animating(false)
    , m_context(0)
    , m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
    timer = new QTimer(parent);
    connect(timer,SIGNAL(timeout()),this, SLOT(updateFrame()));
    timer->start(50);
}


OpenGLWindow::~OpenGLWindow()
{
    delete this->timer;
}

void OpenGLWindow::initialize()
{

}

void OpenGLWindow::updateFrame()
{
    if(m_animating)
        this->renderLater();
}

void OpenGLWindow::render()
{
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());

}

void OpenGLWindow::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);
}

void OpenGLWindow::renderLater()
{
    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool OpenGLWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void OpenGLWindow::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}

void OpenGLWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}
