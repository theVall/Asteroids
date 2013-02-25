/**
 * @file PowerUp.cpp
 * @author Gruppe 2
 */

#include "PowerUp.hpp"

PowerUp::PowerUp(glVector<float> pos, glVector<float> dir, int type, double speed, long lifetime)
{
    Body::randDirection();
    Body::standardAxis();
    
    m_direction = dir;
    m_position  = pos;
    m_lifetime  = lifetime;
    m_speed     = Body::randomNum(-10, 10);
    m_type      = type;
    
    switch (m_type)
    {
        // LP up
        case  1: m_radius = 800; break;
        // Shield
        case  2: m_radius = 800; break;
        default: m_radius = 800; break;
    }
}
      
PowerUp::~PowerUp() { /* nothing to do yet */ }
      
void PowerUp::updatePosition()
{
    Body::updatePosition();
    m_lifetime--;
}

void PowerUp::doAction(Fighter* f)
{
    switch (m_type)
    {
        // LP up
        case 1: f->setLP(f->getLP() + 25); break;
        
        //Shield mode
        case 2: 
        {
            f->setShieldStatus(true);
            Shield* s = new Shield(f->getPosition(), f->getXAxis(), f->getSpeed(), 300);
            f->setShield(s);
        }
        default: break;
    }
}

long PowerUp::getLifetime()    { return m_lifetime; }

void PowerUp::setLifetime(long l) { m_lifetime = l; }
