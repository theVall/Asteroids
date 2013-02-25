/**
 * @file Pushup.hpp
 * @author Gruppe 2 
 */

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "Body.hpp"
#include "rendering/Fighter.hpp"

/**
 * @brief Pushup object.
 */
class PowerUp : public Body
{
  public:
      
      /**
       * @brief Default Constructor
       */
      PowerUp() {};
      
      /**
       * @brief Ctor
       * @param pos position of PowerUp
       * @param dir direction of Powerup
       * @param type type of powerup (1 = hp boost, 2 = shield)
       * @param speed speed of PowerUp
       * @param lifetime lifetime of PowerUp
       */
      PowerUp(glVector<float> pos, glVector<float> dir, int type, double speed, long lifetime);
      
      /**
       * @brief Dtor
       */
      ~PowerUp();
      
      /**
       * @brief upadte position of powerup, decrease lifetime
       */
      void updatePosition();
      
      /**
       * @brief returns lifetime
       * @return lifetime
       */
      long getLifetime();
      
      /**
       * @brief setter for lifetime
       */
      void setLifetime(long l);
      
      /**
       * @brief performs powerup action on fighter
       */
      void doAction(Fighter* f);
      
  private:
      //lifetime
      long m_lifetime;

      //type of pushup
      int m_type;
};

#endif // PowerUp.hpp
