/**
 * @file Fighter.hpp
 * @author Gruppe 2
 */

#ifndef FIGHTER_HPP_
#define FIGHTER_HPP_

#include <GL/glu.h>
#include <GL/glut.h>

#include <vector>

#include "Body.hpp"
#include "Shield.hpp"
#include "TexturedMesh.hpp"
#include "math/glVector.hpp"
#include "Weapon.hpp"

/**
 * @brief   Represents a fighter that can shoot bullets.
 */
class Fighter : public Body
{
    public:
        /**
         * @brief Ctor
         */
        Fighter();
        
        /**
         * @brief Renders the fighter and calls the bullets' render method.
         */
        void render();
        
        /**
         * @brief Shoots the fighter's weapon(s)
         */
        bool shoot();
        
        /**
         * @brief collects information on fighter
         * @return pointer to position, x-, y- and z-axis
         */
        glVector<float> *getInfo();
        
        /**
         * @brief set the shield status
         */
        void setShieldStatus(bool s);
        
        /**
         * @brief get shield status
         */
        bool getShieldStatus();

        /**
         * @brief set shield pointer
         */
        void setShield(Shield* s);

        /**
         * @brief get shield pointer
         */
        Shield* getShield();

        /**
         * @brief Returns the ship's current weapon
         */
        Weapon* getWeapon();

        /**
         * @brief Sets the fighter's weapon
         */
        void setWeapon(Weapon* weapon, int weaponType);

        /**
         * @brief returns weapon type
         */
        int getWeaponType();
        
        /**
         * @brief set LP of fighter
         */
        void setLP(int lp);
        
        /**
         * @brief get LP of fighter
         * @return LP
         */
        int getLP();
        
        /**
         * @brief decrease LP of fighter
         * @param damage LP to be decreased in percent
         */
        void decreaseLP(int damage);

   private:

        //shield enabled?
        bool m_shieldStatus;

        //pointer to shield of fighter
        Shield* m_shield;

        //pointer to weapon
        Weapon* m_weapon;
        
        //weapon type
        int m_weaponType;
        
        //life points (0-100%)
        int m_LP;
};

#endif /* Fighter.hpp */
