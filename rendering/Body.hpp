/**
 * @file Body.hpp
 * @author Gruppe 2
 */

#ifndef BODY_HPP_
#define BODY_HPP_

#include "TexturedMesh.hpp"
#include "math/glVector.hpp"
#include "math/glNormal.hpp"

#include <GL/glut.h>
#include <GL/glu.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include <QMutex>

/**
 * Basic class representing an object in space like asteroids bullets etc.
 */
class Body: public TexturedMesh
{
    public:

        /**
         * @brief Default Ctor
         */
        Body();

        /**
         * @brief Ctor
         * @param pos position of  object
         * @param dir random direction
         * @param speed random speed
         */
        Body(glVector<float> pos, glVector<float> dir = randDirection(), double speed = randomNum(-10, 10));

        /**
         * @brief Dtor
         */
        ~Body();

        /**
         * @brief updates postion of the object / "moves" object in space
         */
        void updatePosition();

        /**
         * @brief accelerates body
         * @param a acceleration rate
         */
        void accelerate(double a);

        /**
         * @brief calculates distance to another body
         * @param body other body
         * @return distance to other body
         */
        double getDistance(Body *body);

        /**
         * @brief In case of collision: body bounces back in opposite direction.
         * @param opp_dir direction of the other object
         * @param opp_pos position of the other object
         */
        void bounceBack(glVector<float> opp_dir, glVector<float> opp_pos);

        /**
         * @brief speed setter
         * @param s new speed
         */
        void setSpeed(double s);

        /**
         * @brief speed getter
         * @return current speed
         */
        double getSpeed();

        /**
         * @brief max speed setter
         * @param ms new max speed
         */
        void setMaxSpeed(double ms);

        /**
         * @brief max speed getter
         * @return current max speed
         */
        double getMaxSpeed();

        /**
         * @brief x-axis getter
         * @return current x-axis
         */
        glVector<float> getXAxis();

        /**
         * @brief y-axis getter
         * @return current y-axis
         */
        glVector<float> getYAxis();

        /**
         * @brief z-axis getter
         * @return current z-axis
         */
        glVector<float> getZAxis();

        /**
         * @brief direction setter
         * @param dir new direction
         */
        void setDirection(glVector<float> dir);

        /**
         * @brief direction getter
         * @return current direction
         */
        glVector<float> getDirection();

        /**
         * @brief position setter
         * @param vec new position
         */
        void setPosition(glVector<float> vec);

        /**
         * @brief position getter
         * @return current position
         */
        glVector<float> getPosition();

        /**
         * @brief radius getter
         * @return current radius
         */
        double getRadius();

        /**
         * @brief set the direction randomly
         * @return new random direction
         */
        static glVector<float> randDirection();

        /**
         * @brief sets the standard axis (1-1-1)
         */
        void standardAxis();

        /**
         * @brief resizes the object
         * @param size resize factor
         */
        void resize(float size);

        //mutex to lock critical code parts
        QMutex m_pos_mutex;

    protected:

        /**
         * @brief generates a random float in a specified interval
         * @param low lower boundary
         * @param high higher boundary
         * @return random float
         */
        static float randomNum(int low, int high);

        // speed of body
        double m_speed;

        // maximum speed of body
        double m_maxSpeed;

        // Radius of body
    	  double m_radius;

        // direction vectors
        glVector<float> m_direction;
};

#endif /* Body.hpp */
