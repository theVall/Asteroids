/**
 * @file Plasma.hpp
 */

#ifndef __PLASMA_HPP__
#define __PLASMA_HPP__

#include "Weapon.hpp"

/**
 * @brief represents the plasma weapon of fighter.
 */
class Plasma : public Weapon
{
public:
    /** 
     * @brief Ctor
     * @param weaponStatus status of the weapon in percent
     */
    Plasma(double weaponStatus);

    /**
     * @brief Dtor
     */
    ~Plasma();
};

#endif /* __PLASMA_HPP__ */
