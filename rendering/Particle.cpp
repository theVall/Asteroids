/**
 * @file Particle.cpp
 * @author Gruppe 2
 */

#include "Particle.hpp"

Particle::Particle(glVector<float> vec, long lifetime)
{
    Body::randDirection();
    Body::standardAxis();
    
    m_lifetime = lifetime;
    m_speed = Body::randomNum(-5, 5);
    
    float randX  = Body::randomNum(-300, 300);
    float randY  = Body::randomNum(-300, 300);
    float randZ  = Body::randomNum(-300, 300);
    m_position   = vec;
    m_position  += glVector<float>(randX, randY, randZ);
}

Particle::~Particle() {}

void Particle::render()
{
    //render as solid sphere
    // Compute transformation matrix
    computeMatrix();
    // Push old transformation of the OpenGL matrix stack and
    // start rendering the bullet in according to the
    // internal transformation matrix
    glPushMatrix();
    glMultMatrixf(m_transformation);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(10, 16, 16);

    // Pop transformation matrix of this object
    // to restore the previous state of the OpenGL
    // matrix stack
    glPopMatrix();
}

void Particle::updatePosition()
{
    m_lifetime--;
    Body::updatePosition();
}

void Particle::setLifetime(long l) { m_lifetime = l; }

long Particle::getLifetime()    { return m_lifetime; }
