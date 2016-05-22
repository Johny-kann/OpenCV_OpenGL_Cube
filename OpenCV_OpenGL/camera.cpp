#include "camera.h"

Camera::Camera()
{
    position_axis.setX(0);
    position_axis.setY(0);
    position_axis.setZ(0);

    angle.setX(0);
    angle.setY(0);
    angle.setZ(0);


}

void Camera::position(float x, float y, float z)
{
    position_axis.setX(x);
    position_axis.setY(y);
    position_axis.setZ(z);
}

void Camera::addAngles(float x, float y, float z)
{
    angle.setX(angle.x()+x);
    angle.setY(angle.y()+y);
    angle.setZ(angle.z()+z);
}

void Camera::addPos(float x, float y, float z)
{

}
