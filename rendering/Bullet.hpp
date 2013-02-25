/**
 * @file Bullet.hpp
 * @author Gruppe 2 
 */

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "Body.hpp"

/**
 * @brief Bullet object.
 */
class Bullet : public Body
{
  public:
  		Bullet() {};
  		
      /**
       * @brief Ctor
       * @param pos position where bullet spawnes
       * @param dir random direction
       * @param speed random speed
       * @param range default: 100
       * @param damage default: 100
       */
      Bullet(glVector<float> pos, glVector<float> dir = randDirection(), double speed = randomNum(-10, 10), int range = 100, int damage = 100);
      
      /**
       * @brief Dtor
       */
      ~Bullet();
      
      /**
       * @brief renders the bullet
       */
      void render();
      
      /**
       * @brief update position of bullet, decrease lifetime
       */
      void updatePosition();

      /**
       * @brief returns lifetime
       */
      long getLifetime();
      
      /**
       * @brief setter for lifetime
       */
      void setLifetime(long l);
      
      /**
       * @brief get damage of bullet
       * @return damage
       */
      int getDamage();
      
      /**
       * @brief set damage of bullet 
       */
      void setDamage(int damage);
      
  private:
        // lifetime
        long m_lifetime;
        
        //damage that bullet deals (weapon dependant)
        int m_damage;
};

#endif // Bullet.hpp
