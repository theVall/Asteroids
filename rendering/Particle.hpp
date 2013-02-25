/**
 * @file Particle.hpp
 * @author Gruppe 2
 */

#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include "Body.hpp"

/**
 * @brief Represents a particle objects which is created when a asteroid is hit.
 */
class Particle : public Body
{
  public:
    
    /**
     * @brief Ctor
     * @param pos position of particle
     * @param lifetime lifetime of the particle
     */
    Particle(glVector<float> pos, long lifetime);

    /**
     * @brief Dtor
     */
    ~Particle();

    /**
     * @brief renders the particle
     */
    void render();

    /**
     * @brief set lifetime of particle
     * @param l lifetime
     */
    void setLifetime(long l);
    
    /**
     * @brief returns the lifetime of particle
     * @return lifetime
     */
    long getLifetime();

    /**
     * @brief update position of particle, decrease lifetime
     */
    void updatePosition();
    
  private:
        
    // lifetime of particle
    long m_lifetime;    
};

#endif // Particle.hpp
