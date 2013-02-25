/**
 *  @file Camera.hpp
 *  @author Gruppe 2
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <cmath>
#include "math/Global.hpp"
#include "math/Quaternion.hpp"
#include "math/glVector.hpp"
#include "math/glNormal.hpp"
#include "rendering/Fighter.hpp"
#include <list>

/**
 * @brief   A small, far from perfect camera class for our viewer
 */
class Camera
{
    public:
        /**
         * @brief   Constructs a camera object
         */
        Camera();

        /**
         * @brief   Contructs a camera object at the given position
         * @param x value of x
         * @param y value of y
         * @param z value of z
         */
        Camera(float x, float y, float z);

        /**
         * @brief   Deletes the camera
         */
        virtual ~Camera() {};

        /**
         * @brief   Moves the camera left by m_speed units
         */
        void moveLeft();

        /**
         * @brief   Moves the camera right by m_speed units
         */
        void moveRight();

        /**
         * @brief   Moves the camera up by m_speed units
         */
        void moveUp();

        /**
         * @brief   Moves the camera down by m_speed units
         */
        void moveDown();

        /**
         * @brief   Moves the camera forward by m_speed units
         */
        void moveForward();

        /**
         * @brief   Moves the camera backwards by m_speed units
         */
       void moveBackward();

        /**
         * @brief   Turns left by m_rotSpeed units
         */
        void turnLeft();

        /**
         * @brief   Turns right by m_rotSpeed units
         */
        void turnRight();

        /**
         * @brief   Turns up by m_rotSpeed units
         */
        void turnUp();

        /**
         * @brief   Turns down by m_rotSpeed units
         */
        void turnDown();

        /**
         * @brief   Sets the current movement speed
         * @param speed Movement speed
         */
        void setSpeed(float _speed){m_speed = _speed;};

        /**
         * @brief   Sets the current turn speed
         * @param speed turn speed
         */
        void setTurnSpeed(float _speed) {m_turnSpeed = _speed;};

        /**
         * @brief sets position of camera to given position
         * @param Vector with coordinades
         */
         void setPosition(glVector<float> vec);

        /**
         *  @brief sets direction of the camera
         *  @param Vector with direction
         */
         void setDirection(glVector<float> dir);

        /**
         * @brief sets camera position on top of fighter
         * @param f fighter
         */
        void setToFighter(Fighter* f);

        /**
         * @brief   Increases the the current speed by \ref addSpeed units
         * @param addSpeed Units to increase
         */
        void incSpeed(float addSpeed){m_speed += addSpeed;};

        /**
         * @brief   Increases the the current turn speed by \ref decSpeed units
         * @param decSpeed Units to increase
         */
        void incTurnSpeed(float decSpeed){m_turnSpeed += decSpeed;};

        /**
         * @brief Applies the current camera transformation to the OpenGL matrix stack
         */
        void apply();

        /**
         * @brief applies camera rotation only
         */
        void applyRotationOnly();

        /**
         * @brief sets new location
         * @param pos position in space
         * @param dir direction in space
         * @param up
         */
	void setLocation(glVector<float>pos, glVector<float> dir, glVector<float> up);

        // current position
	glVector<float> m_pos;

	glVector<float> m_realpos;
        //
	std::list< glVector<float> > m_list_pos;

        //
	std::list< glVector<float> > m_list_cam;

        //
	std::list< glVector<float> > m_list_up;

    private:
        // current orientation of the x-axis, y-axis and z-axis
        glVector<float> m_baseX, m_baseY, m_baseZ;

        // current speed and turning speed
        float m_speed, m_turnSpeed;

        // current rotation aroung x-axis and y-axis
        float m_rotX, m_rotY;

        // current x, y and z position
        float m_px, m_py, m_pz;

        // initial x, y and z position
        float m_ix, m_iy, m_iz;

        //The x, y and z component of the "look at" vector
        float m_lx, m_ly, m_lz;

        //
        float m_above, m_behind;

        //
        glVector<float> m_direction, m_up;

        //
        glVector<float> m_cam;

};

#endif /* Camera.hpp */
