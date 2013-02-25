/**
 * @file Shield.cpp
 * @author Gruppe 2
 */

#include "Shield.hpp"

Shield::Shield(glVector<float> pos, glVector<float> dir, double speed, long lifetime)
{
    Body::standardAxis();

    m_direction = dir;
    m_radius    = 230;
    m_position  = pos;
    m_speed     = speed;
    m_lifetime  = lifetime;
}

Shield::~Shield() { /* nothing to do yet */ }

void Shield::render()
{
    // render the shield as a glut wire sphere
    computeMatrix();
    glPushMatrix();
    glMultMatrixf(m_transformation);

    glDisable(GL_LIGHTING); 
    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(m_radius, 20, 20);
    glEnable(GL_LIGHTING);
   
   glPopMatrix();
}

void Shield::updatePosition()
{
    Body::updatePosition();
    m_lifetime--;
}

long Shield::getLifetime()       { return m_lifetime; }

void Shield::setLifetime(long l) { m_lifetime = l; }
