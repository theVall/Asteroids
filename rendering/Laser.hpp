/**
 * @file Laser.hpp
 * @author Gruppe 2
 */
#ifndef __LASER_HPP__
#define __LASER_HPP__

#include "Weapon.hpp"

/**
 * @brief represends the laser weapon.
 */
class Laser : public Weapon
{
public:
    /**
     * @brief Ctor
     * @param WeaponStatus status of the weapon in percent
     */
    Laser(double weaponStatus);

    /**
     * @brief Dtor
     */
    ~Laser();
};
#endif /*__LASER_HPP__ */

