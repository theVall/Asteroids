/**
 * @file Camera.cpp
 * @author Gruppe 2
 */

#include "Camera.hpp"

#include <GL/gl.h>      /* Header File For The OpenGL32 Library */
#include <GL/glu.h>     /* Header File For The GLu32 Library */

Camera::Camera()
{
    m_baseX = glVector<float>(1.0, 0.0, 0.0);
    m_baseY = glVector<float>(0.0, 1.0, 0.0);
    m_baseZ = glVector<float>(0.0, 0.0, 1.0);
	m_px =          0.0;
	m_py =          0.0;
	m_pz =          0.0;

	m_ix =          0.0;
	m_iy =          20.0;
	m_iz =          100.0;
	m_turnSpeed =   0.02;
	m_speed =       20;

	m_rotX =        0.0;
	m_rotY =        0.0;

	m_above = 100.0;
	m_behind = 600.0;

	m_direction = glNormal<float>(1.0,1.0,1.0);
	m_up = glNormal<float>(1.0,1.0,1.0);
}

Camera::Camera(float x, float y, float z){
    m_baseX = glVector<float>(1.0, 0.0, 0.0);
    m_baseY = glVector<float>(0.0, 1.0, 0.0);
    m_baseZ = glVector<float>(0.0, 0.0, 1.0);

	m_px = 0.0;
	m_py = 0.0;
	m_pz = 0.0;
	m_lx = m_ly = 0.0;
	m_lz = 0.0;
	m_speed = m_turnSpeed = 0.2;
	m_ix = x;
	m_iy = y;
	m_iz = z;

	m_rotX = 0.0;
	m_rotY = 0.0;
	m_above = 500.0;
	m_behind = 500.0;

	m_direction = glNormal<float>(1.0,1.0,1.0);
	m_up = glNormal<float>(1.0,1.0,1.0);
}

void Camera::setToFighter(Fighter* f)
{
    m_px = f->getPosition().x;
    m_py = f->getPosition().y;
    m_pz = f->getPosition().z *(-1) - 1000;
    m_baseX = (f->getXAxis())*(-1);
    m_baseY = (f->getYAxis())*(-1);
    m_baseZ = (f->getZAxis())*(-1);
}


void Camera::moveLeft()
{
	m_px -= m_speed * sin(PH - m_rotY);
	m_pz -= m_speed * cos(PH - m_rotY);
}

void Camera::moveRight()
{
	m_px += m_speed * sin(PH + m_rotY);
	m_pz += m_speed * cos(PH + m_rotY);
}

void Camera::moveForward()
{
	m_px += m_speed * sin(m_rotY);
	m_pz += m_speed * cos(m_rotY);
}
void Camera::moveBackward()
{
	m_px -= m_speed * sin(m_rotY);
	m_pz -= m_speed * cos(m_rotY);
}

void Camera::turnUp()
{
	if(m_rotX < PH)
	{
		m_rotX -= m_turnSpeed;

		// Transform base
//		Quaternion nq(m_baseX, -m_turnSpeed);
//		m_baseY = nq * m_baseY;
//		m_baseZ = nq * m_baseZ;
	}
}

void Camera::turnDown()
{
	if(m_rotX > -PH)
	{
		m_rotX += m_turnSpeed;

		//Transform base
//		Quaternion nq(m_baseX, m_turnSpeed);
//		m_baseY = nq * m_baseY;
//		m_baseZ = nq * m_baseZ;
	}
}

void Camera::turnLeft()
{
	m_rotY -= m_turnSpeed;

	//Transform base
	Quaternion<float> nq(m_baseY, m_turnSpeed);
	m_baseX = nq * m_baseX;
	m_baseZ = nq * m_baseZ;
}

void Camera::turnRight()
{
	m_rotY += m_turnSpeed;

    //Transform base
    Quaternion<float> nq(m_baseY, -m_turnSpeed);
    m_baseX = nq * m_baseX;
    m_baseZ = nq * m_baseZ;
}

void Camera::moveUp()
{
	m_py += m_speed;
}


void Camera::moveDown()
{
	m_py -= m_speed;
}

void Camera::applyRotationOnly()
{
    glLoadIdentity();
    gluLookAt(0, 0, 0, 0, 0, 0, m_up.x, m_up.y, m_up.z);
}

void Camera::setLocation(glVector<float> pos, glVector<float> direction, glVector<float> up) {

    // Clear matrix stack
    glLoadIdentity();

    m_direction = glNormal<float>(direction);
    m_up = glNormal<float>(up);

    glVector<float> cam = pos + m_up * m_above + m_direction * m_behind;
    m_pos = pos + (m_up * m_above);
    m_cam = cam;

    //m_list_pos.push_back(m_pos);
    m_list_cam.push_back(m_cam);
    m_list_up.push_back(m_up);

    //m_realpos = m_list_pos.front() - (m_list_up.front() * m_above);
    if(m_list_cam.size() > 5)
    {
	    //m_list_pos.pop_front();
	    m_list_cam.pop_front();
	    m_list_up.pop_front();
    }
    //m_pos = m_list_pos.front();
    m_cam = m_list_cam.front();
    m_up = m_list_up.front();

    // Calc transformation Matrixwf
    gluLookAt(cam.x, cam.y, cam.z,
              m_pos.x, m_pos.y, m_pos.z,
              m_up.x , m_up.y , m_up.z);

}

void Camera::apply()
{
    // Create position and look at vector
    m_lx = m_ix + m_px + sin(m_rotY);
    m_lz = m_iz - m_pz - cos(m_rotY);
    m_ly = m_iy + m_py + sin(m_rotX);

    // Clear matrix stack
    glLoadIdentity();

    // Calc transformation matrix
    gluLookAt(m_ix + m_px, m_iy + m_py, m_iz - m_pz,
            m_lx, m_ly, m_lz,
            0.0, 1.0, 0.0);
}
void Camera::setPosition(glVector<float> vec)
{
    m_px = vec.x;
    m_py = vec.y;
    m_pz = vec.z;
}
void Camera::setDirection(glVector<float> dir)
{
    m_lx = dir.x;
    m_ly = dir.y;
    m_lz = dir.z;
}
