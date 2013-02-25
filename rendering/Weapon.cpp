/**
 * @file Weapon.cpp
 *
 * @author Jannis Eichborn (jeichborn@uos.de)
 * @date 27.2.2012
 */

#include "Weapon.hpp"

Weapon::Weapon(int range, int damage, double speed, int energy, double refresh)
{
    m_range = range;
    m_damage = damage;
    m_speed = speed;
    m_energy = energy;
    m_refresh = refresh;
    m_weaponStatus = 100;
}

Weapon::Weapon() {}

Weapon::~Weapon() {}

void Weapon::refresh()
{
    if(m_weaponStatus + m_refresh < 101.0)
    {
        m_weaponStatus += m_refresh;
    }
}

bool Weapon::shoot()
{
    if(m_weaponStatus - m_energy > 0)
    {
        m_weaponStatus -= m_energy;
        return true;
    }
    else
    {
        return false;
    }
}

//getters and setters
int Weapon::getRange()        { return m_range; }

int Weapon::getDamage()       { return m_damage; }

double Weapon::getSpeed()     { return m_speed; }

double Weapon::getRefresh()   { return m_refresh; }

int Weapon::getEnergy()       { return m_energy; }

int Weapon::getWeaponStatus() { return int(m_weaponStatus); }

void Weapon::setWeaponStatus(double status) { m_weaponStatus = status; }

