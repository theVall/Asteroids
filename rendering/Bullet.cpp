/**
 * @file Bullet.cpp
 * @author Gruppe 2
 */

#include "Bullet.hpp"


Bullet::Bullet(glVector<float> pos, glVector<float> dir, double speed, int range, int damage)
	: Body(pos, dir, speed), m_lifetime(int(range/speed)), m_damage(damage) 
{
    m_radius = 10;
}

Bullet::~Bullet() { /* nothing to do yet */ }

void Bullet::render()
{
	  TexturedMesh::render();
}

void Bullet::updatePosition()
{
    Body::updatePosition();
    m_lifetime--;
}

//getter - setter
long Bullet::getLifetime()         { return m_lifetime; }

void Bullet::setLifetime(long l)   { m_lifetime = l; }

int Bullet::getDamage()            { return m_damage; }

void Bullet::setDamage(int damage) { m_damage = damage; }
