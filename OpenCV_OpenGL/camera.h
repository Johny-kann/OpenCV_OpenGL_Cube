#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>

class Camera
{
public:
    Camera();

    void position(float x,float y,float z);
    void angles(float x,float y,float z);

    void addAngles(float x,float y,float z);
    void addPos(float x,float y,float z);

    QVector3D position_axis;
    QVector3D angle;
};

#endif // CAMERA_H
