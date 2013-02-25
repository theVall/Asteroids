/**
 * @file Weapon.hpp
 *
 * @author Jannis Eichborn (jeichborn@uos.de)
 * @date 27.2.2012
 *
 * @brief Represents a weapon with its parameters.
 */
#ifndef __WEAPON_HPP__
#define __WEAPON_HPP__

class Weapon
{
public:
    /**
     * @brief Constructor which sets up all parameters
     * @param range range of the weapon
     * @param damage damage of the weapon
     * @param speed speed of the bullets shot by this weapon
     * @param energy energy used while shooting bullets
     * @param refresh refresh rate of energy
     */
    Weapon(int range, int damage, double speed, int energy, double refresh);

    /**
     * @brief default constructor
     */
    Weapon();

    /**
     * @brief Destructor
     */
    ~Weapon();

    /**
     * @brief Tries to shoot the weapon
     * @return True if could shoot, else false
     */
    bool shoot();

    /**
     * @brief Refreshes the Weapon
     */
    void refresh();

    /**
     * @brief Retrieve the range of the weapon
     * @return range
     */
    int getRange();

    /**
     * @brief Retrieve the damage the weapon causes
     * @return damage
     */
    int getDamage();

    /**
     * @brief Retrieve the refresh rate of the weapon
     * @return refresh rate
     */
    double getRefresh();

    /**
     * @brief Retrieve the energy consumption of the weapon
     * @return energy
     */
    int getEnergy();

    /**
     * @brief Retrieve the bullet's speed
     * @return speed of bullets
     */
    double getSpeed();

    /**
     * @brief Retrieve the current energy-level of the weapon
     * @return weapon status
     */
    int getWeaponStatus();

    /**
     * @brief Sets the energy level of the weapon
     * @param status weapon status
     */
    void setWeaponStatus(double status);

protected:
    // The range of the weapon
    int m_range;
    // The damage it causes
    int m_damage;
    // The speed of the projectiles
    double m_speed;
    // The refresh rate
    double m_refresh;
    // The energy consumption of the weapon
    int m_energy;
    // The current energy-level of the weapon
    double m_weaponStatus;
};

#endif /* __WEAPON_HPP__ */
