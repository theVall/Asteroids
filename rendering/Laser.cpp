/**
 * @file Laser.cpp
 * @author Gruppe 2
 */

#include "Laser.hpp"

Laser::Laser(double weaponStatus)
{
    //initial values of laser weapon
    m_range        = 25000;
    m_damage       =    20;
    m_speed        =   300.0;
    m_energy       =    10;
    m_refresh      =     0.2;
    m_weaponStatus = weaponStatus;
}

Laser::~Laser() { }
