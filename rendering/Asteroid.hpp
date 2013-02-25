/**
 * @file Asteroid.hpp
 * @author Gruppe 2
 */

#ifndef ASTEROID_HPP_
#define ASTEROID_HPP_

#include "Body.hpp"

/**
 * @brief Represents an asteroid object in space. The Asteroid has a size, life points (LP) and rotates.
 */
class Asteroid : public Body
{
    public:

      /**
       * @brief default constructor
       */
      Asteroid() {}

      /**
       * @brief constructor
       * @param pos position of asteroid
       * @param dir a random direction
       * @param size 1 -> big asteroid
       * @param speed random speed
       */
      Asteroid(glVector<float> pos, glVector<float> dir = randDirection(), float size = 1, double speed = randomNum(-10, 10));

      /**
       * @brief destructor
       */
      ~Asteroid();

      /**
       * @brief Override of Body function to use rotation in addition.
       */
      void updatePosition();

      /**
       * @brief rotate the asteroid
       * @param axis around which the asteroid shall be rotated
       * @param s speed of rotation
       */
      void rotate(int axis, float s);
      
      /**
       * @brief decrease LP of asteroid
       * @param damage LP to be decreased from asteroid in percent.
       */
      void decreaseLP(int damage);

      /**
       * @brief get LP of asteroid
       * @return LP
       */
      int getLP();

    private:

      //life points
      int m_LP;
      //size of asteroid (1 = big, 2 = small)
      int m_size;
      //x rotation
      float m_rotX;
      //y rotation
      float m_rotY;
      //z rotation
      float m_rotZ;
};

#endif // Asteroid.hpp
