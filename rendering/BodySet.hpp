 /**
 * @file BodySet.hpp
 * @author Gruppe 2
 */

#ifndef BODYSET_HPP_
#define BODYSET_HPP_

#include <boost/ptr_container/ptr_list.hpp>
#include <QMutex>
#include <vector>

#include "Body.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"
#include "PowerUp.hpp"
#include "Particle.hpp"
#include "math/glVector.hpp"
#include "io/SoundOutput.hpp"

/**
 * @brief Represents a set of body objects to quickly iterate over them for collision check etc.
 */
class BodySet
{
    public:
        /**
         * @brief Contructor. Builds a set of Body-Objects, which updates these objects.
         */
        BodySet();

        /**
         * @brief Destructor
         */
        ~BodySet();

        /**
         * @brief Adds a bullet to the set.
         * @param b bullet pointer to be added
         */
        void add(Bullet* b);

        /**
         * @brief Adds an asteroid to the set.
         * @param a asteroid pointer to be added
         */
        void add(Asteroid* a);

        /**
         * @brief Adds a powerUp to the set.
         * @param p PowerUp pointer to be added
         */
        void add(PowerUp* p);
        
        /**
         * @brief Adds a particle to the set.
         * @param p particle pointer to be added
         */
        void add(Particle* pa);
        
        /**
         * @brief Moves the Body-Objects until it's lifetime is over.
         */
        void run();

        /**
         * @brief Renders the Body-Objects.
         */
        void renderAll(glVector<float> fighterPos, glVector<float> fighterDir);

        /**
         * @brief erase asteroid from pointer list
         * @param iterator it on element to be erased
         */
        boost::ptr_list<Asteroid>::iterator eraseAsteroid(boost::ptr_list<Asteroid>::iterator it);

        /**
         * @brief erase bullet from pointer list
         * @param iterator it on element to be erased
         */
        boost::ptr_list<Bullet>::iterator eraseBullet(boost::ptr_list<Bullet>::iterator it);

        /**
         * @brief erase particle from pointer list
         * @param iterator it on element to be erased
         */
        boost::ptr_list<Particle>::iterator eraseParticle(boost::ptr_list<Particle>::iterator it);
        
        /**
         * @brief erase PowerUp from pointer list
         * @param iterator it on element to be erased
         */
        boost::ptr_list<PowerUp>::iterator erasePowerUp(boost::ptr_list<PowerUp>::iterator it);

        /**
         * @brief update positions of all objects
         */
        void updateAllPositions();

        /**
         * @brief asteroid list getter
         * @return current list of active asteroids
         */
        boost::ptr_list<Asteroid>* getAsteroids();

        /**
         * @brief bullet list getter
         * @return current pointer list of active bullets
         */
        boost::ptr_list<Bullet>* getBullets();

        /**
         * @brief PowerUp list getter
         * @return current pointer list of active PoweruUps
         */
        boost::ptr_list<PowerUp>* getPowerUps();

        /**
         * @brief positons vector getter
         * @return current vector of positions
         */
        std::vector<glVector<float> >* getPositions();

        //indicator wheather thread is running
        //runs while run == true
        bool m_running;

        //Mutex to lock critical code parts
        QMutex m_mutex;

    private:
        // lists of pointers to asteroids
        boost::ptr_list<Asteroid> m_asteroids_ptr;

        // list of pointers to bullets
        boost::ptr_list<Bullet> m_bullets_ptr;

        // list of pointers to powerUps
        boost::ptr_list<PowerUp> m_powerups_ptr;

        // list of pointers to particles
        boost::ptr_list<Particle> m_particles_ptr;
        
        // sound output
        SoundOutput sound;

        // positions of bodies
        std::vector<glVector<float> > m_positions;
};

#endif /* BodySet.hpp */
