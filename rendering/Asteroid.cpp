/**
 * @file Asteroid.cpp
 * @author Gruppe 2
 */

#include "Asteroid.hpp"

Asteroid::Asteroid(glVector<float> pos, glVector<float> dir, float size, double speed)
    :Body(pos, dir, speed)
{
            m_size = size;
            //1700 is radius of bounding sphere around big asteroid object.
            m_radius = size * 1700;
            //LP start at 100%
            m_LP     = size * 100;

            m_xAxis  = m_xAxis * size;
            m_yAxis  = m_yAxis * size;
            m_zAxis  = m_zAxis * size;

            //radom rotation
            m_rotX = Body::randomNum(0, 1) / 1000.0;
            m_rotY = Body::randomNum(0, 1) / 1000.0;
            m_rotZ = Body::randomNum(0, 1) / 1000.0;
}

Asteroid::~Asteroid() { /* nothing to do yet */ }

void Asteroid::updatePosition()
{
    //if asteroid is a big one rotate
    //(small ones get problems with scaling and rotation)
    if(m_radius > 1500)
    {
        rotate(PITCH, m_rotX);
        rotate(ROLL, m_rotY);
        rotate(YAW, m_rotZ);
    }

    Body::updatePosition();
}

void Asteroid::rotate(int axis, float s)
{
    Quaternion<float> nq;

    // Get the wanted operation and calculate the new coordinates
    switch(axis)
    {
    case PITCH:
        nq.fromAxis(m_yAxis, s);
        m_xAxis = nq * m_xAxis ;
        m_zAxis = nq * m_zAxis ;
        break;

    case YAW:
        nq.fromAxis(m_xAxis, s);
        m_yAxis = nq * m_yAxis ;
        m_zAxis = nq * m_zAxis ;
        break;

    case ROLL:
        nq.fromAxis(m_zAxis, s);
        m_yAxis = nq * m_yAxis ;
        m_xAxis = nq * m_xAxis ;
        break;
    }

    // Update mesh rotation
    m_rotation = m_rotation * nq ;
}


void Asteroid::decreaseLP(int damage)
{
    m_LP -= damage;
}

int Asteroid::getLP() { return m_LP; }

