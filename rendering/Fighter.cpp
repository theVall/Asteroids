/**
 * @file Fighter.cpp
 * @author Gruppe 2
 */

#include "Fighter.hpp"

Fighter::Fighter()
{
    //100%
    m_LP = 100;
    //no shield
    m_shieldStatus = false;
}

void Fighter::render()
{
    TexturedMesh::render();
    //render shield if enabled and decrease its lifetime
    if(m_shieldStatus)
    {
        m_shield->setPosition(this->getPosition());
        m_shield->render();
        m_shield->setLifetime(m_shield->getLifetime() - 1);
        if (m_shield->getLifetime() < 0)
        {
            m_shieldStatus = false;
        }
    }
}

glVector<float>* Fighter::getInfo()
{
    glVector<float> *result = new glVector<float>[4];
    result[0] = Body::getPosition();
    result[1] = Body::getXAxis();
    result[2] = Body::getYAxis();
    result[3] = Body::getZAxis();
    return result;
}

bool Fighter::shoot()
{
    return m_weapon->shoot();
}

void Fighter::setWeapon(Weapon* weapon, int weaponType)
{
    m_weapon = weapon;
    m_weaponType = weaponType;
}

void Fighter::decreaseLP(int damage)
{
    m_LP -= damage;
}

//getters and setters
void Fighter::setShield(Shield* s) { m_shield = s; }

Shield* Fighter::getShield() { return m_shield; }

void Fighter::setShieldStatus(bool s) { m_shieldStatus = s; }

bool Fighter::getShieldStatus() { return m_shieldStatus; }

Weapon* Fighter::getWeapon(){ return m_weapon; }

int Fighter::getWeaponType() { return m_weaponType; }

void Fighter::setLP(int lp) { m_LP = lp; }

int Fighter::getLP() { return m_LP; }
