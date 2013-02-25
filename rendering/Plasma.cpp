/**
 * @file Plasma.cpp
 */

#include "Plasma.hpp"

Plasma::Plasma(double weaponStatus)
{
    //initial values for plasma weapon
    m_range = 50000;
    m_damage = 50;
    m_speed = 200.0;
    m_energy = 25;
    m_refresh = 0.2;
    m_weaponStatus = weaponStatus;
}

Plasma::~Plasma()
{

}
