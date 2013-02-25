/**
 * @file Body.cpp
 * @author Gruppe 2
 */

#include "Body.hpp"
#include <iostream>

Body::Body()
{
    standardAxis();
}

Body::Body(glVector<float> pos, glVector<float> dir, double speed)
	:  m_speed(speed), m_direction(dir)
{
    standardAxis();
    m_position = pos;
}

Body::~Body() { /* nothing to do yet */ }

void Body::updatePosition()
{
    glNormal<float> dir(m_direction);
    m_pos_mutex.lock();
    m_position = m_position + dir * m_speed;
    m_pos_mutex.unlock();
}

void Body::accelerate(double a)
{
    if(m_speed > m_maxSpeed)
    {
        m_speed = m_maxSpeed;
    }
    else if(m_speed < -m_maxSpeed)
    {
        m_speed = -m_maxSpeed;
    }
    else
    {
        m_speed += a;
    }
}

double Body::getDistance(Body *body)
{
    return body->m_position.dist(m_position);
}

void Body::bounceBack(glVector<float> opp_dir, glVector<float> opp_pos)
{
    glVector<float> diff = opp_pos - m_position;
    if ((diff + m_direction) < diff)
    {
        m_direction  = opp_dir;
    }
}

float Body::randomNum(int low, int high)
{
    float r = high * 1000 - low * 1000 - 1;
    float erg = (float)(low * 1000 + (int)(r * rand()/(RAND_MAX + 1.0)));
    erg /= 1000;
    return erg;
}

glVector<float> Body::randDirection()
{
    float dirx  = randomNum(-1, 1),
          diry  = randomNum(-1, 1),
          dirz  = randomNum(-1, 1);

    return glVector<float>(dirx, diry, dirz);
}

void Body::standardAxis()
{
    m_xAxis     = glVector<float>(1.0, 0.0, 0.0);
    m_yAxis     = glVector<float>(0.0, 1.0, 0.0);
    m_zAxis     = glVector<float>(0.0, 0.0, 1.0);
}

void Body::resize(float size)
{
    m_xAxis = m_xAxis * size;
    m_yAxis = m_yAxis * size;
    m_zAxis = m_zAxis * size;
}

//getter and setter

void   Body::setSpeed(double s)              { m_speed = s; }

double Body::getSpeed()                      { return m_speed; }

void   Body::setMaxSpeed(double ms)          { m_maxSpeed = ms; }

double Body::getMaxSpeed()                   { return m_maxSpeed; }

glVector<float> Body::getXAxis()             { return m_xAxis; }

glVector<float> Body::getYAxis()             { return m_yAxis; }

glVector<float> Body::getZAxis()             { return m_zAxis; }

void Body::setDirection(glVector<float> dir) { m_direction = dir; }

glVector<float> Body::getDirection()         { return m_direction; }

void Body::setPosition(glVector<float> vec)  { m_position = vec; }

glVector<float> Body::getPosition()          { return m_position; }

double Body::getRadius()                     { return m_radius; }

