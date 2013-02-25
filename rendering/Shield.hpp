/**
 * @file Shield.hpp
 * @author Gruppe 2 
 */

#ifndef SHIELD_HPP_
#define SHIELD_HPP_

#include "Body.hpp"

/**
 * @brief Shield which appears for a brief time while fighter gets hit by an asteroid.
 */
class Shield : public Body
{
  public:
      
      /**
       * @brief Ctor
       * @param pos position of the shield (usually around fighter)
       * @param dir direction of the shield (usually equals fighter)
       * @param speed spee of the shield (usually equals fighter)
       * @param lifetime lifetime of the shield
       */
      Shield(glVector<float> pos, glVector<float> dir, double speed, long lifetime);
      
      /**
       * @brief Dtor
       */
      ~Shield();
      
      /**
       * @brief renders the shield as a glut WireSphere
       */
      void render();
      
      /**
       * @brief upadte position of shield, decrease lifetime
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

  private:
        // lifetime
        long m_lifetime;
};

#endif // Shield.hpp

