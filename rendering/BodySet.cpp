/**
 * @file BodySet.cpp
 * @author Gruppe 2
 */

#include "BodySet.hpp"

BodySet::BodySet() { }

BodySet::~BodySet()
{
    m_positions.clear();
    m_asteroids_ptr.clear();
    m_bullets_ptr.clear();
    m_powerups_ptr.clear();
    m_particles_ptr.clear();
}

// add operations
void BodySet::add(Asteroid* a)
{
    m_asteroids_ptr.push_back(a);
}

void BodySet::add(Bullet* b)
{
    m_bullets_ptr.push_back(b);
}

void BodySet::add(PowerUp* p)
{
    m_powerups_ptr.push_back(p);
}

void BodySet::add(Particle* pa)
{
    m_particles_ptr.push_back(pa);
}

//erase operations
boost::ptr_list<Asteroid>::iterator BodySet::eraseAsteroid(boost::ptr_list<Asteroid>::iterator it)
{
    m_mutex.lock();
    boost::ptr_list<Asteroid>::iterator ret;
    ret = m_asteroids_ptr.erase(it);
    m_mutex.unlock();
    return ret;
}

boost::ptr_list<Bullet>::iterator BodySet::eraseBullet(boost::ptr_list<Bullet>::iterator it)
{
    m_mutex.lock();
    boost::ptr_list<Bullet>::iterator ret;
    ret = m_bullets_ptr.erase(it);
    m_mutex.unlock();
    return ret;
}

boost::ptr_list<Particle>::iterator BodySet::eraseParticle(boost::ptr_list<Particle>::iterator it)
{
    m_mutex.lock();
    boost::ptr_list<Particle>::iterator ret;
    ret = m_particles_ptr.erase(it);
    m_mutex.unlock();
    return ret;
}

boost::ptr_list<PowerUp>::iterator BodySet::erasePowerUp(boost::ptr_list<PowerUp>::iterator it)
{
    m_mutex.lock();
    boost::ptr_list<PowerUp>::iterator ret;
    ret = m_powerups_ptr.erase(it);
    m_mutex.unlock();
    return ret;
}

void BodySet::renderAll(glVector<float> fighterPos, glVector<float> fighterDir)
{
    m_mutex.lock();
    boost::ptr_list<Body>::iterator it;
    for(it = m_asteroids_ptr.begin(); it != m_asteroids_ptr.end(); it++)
    {
        glVector<float> diff = fighterPos - it->getPosition();
        if(diff * fighterDir > 0)
        {
            float dist = fighterPos.dist(it->getPosition());
            float size = 0;
            if(dist < 100000)
            {
                if(dist < 50000) size = 1;
                else size = (100000 - dist) / 50000;
            }
            it->resize(size);
            it->render();
        }
    }
    for(it = m_bullets_ptr.begin(); it != m_bullets_ptr.end(); it++)
    {
        it->render();
    }
    for(it = m_powerups_ptr.begin(); it != m_powerups_ptr.end(); it++)
    {
        it->render();
    }
    for(it = m_particles_ptr.begin(); it != m_particles_ptr.end(); it++)
    {
        it->render();
    }
    m_mutex.unlock();
}

void BodySet::updateAllPositions()
{
    m_mutex.lock();

    boost::ptr_list<Asteroid>::iterator it_asteroids = m_asteroids_ptr.begin();
    m_positions.clear();

    while (it_asteroids != m_asteroids_ptr.end())
    {
        it_asteroids->updatePosition();
        m_positions.push_back(it_asteroids->getPosition());
        it_asteroids++;
    }

    boost::ptr_list<Bullet>::iterator it_bullets = m_bullets_ptr.begin();
    while (it_bullets != m_bullets_ptr.end())
    {
        it_bullets->updatePosition();
        if (it_bullets->getLifetime() < 0)
        {
            it_bullets = m_bullets_ptr.erase(it_bullets);
        }
        else
        {
            it_bullets++;
        }
    }

    boost::ptr_list<PowerUp>::iterator it_powerups = m_powerups_ptr.begin();
    while (it_powerups != m_powerups_ptr.end())
    {
        it_powerups->updatePosition();
        if (it_powerups->getLifetime() < 0)
        {
            it_powerups = m_powerups_ptr.erase(it_powerups);
        }
        else
        {
            it_powerups++;
        }
    }
    
    boost::ptr_list<Particle>::iterator it_particles = m_particles_ptr.begin();
    while (it_particles != m_particles_ptr.end())
    {
        it_particles->updatePosition();
        if (it_particles->getLifetime() < 0)
        {
            it_particles = m_particles_ptr.erase(it_particles);
        }
        else
        {
            it_particles++;
        }
    }

    m_mutex.unlock();
}

//getter methods
boost::ptr_list<Asteroid>* BodySet::getAsteroids()     { return &m_asteroids_ptr; }

boost::ptr_list<Bullet>*   BodySet::getBullets()       { return &m_bullets_ptr; }

boost::ptr_list<PowerUp>*  BodySet::getPowerUps()      { return &m_powerups_ptr; }

std::vector<glVector<float> >* BodySet::getPositions() { return &m_positions; }
