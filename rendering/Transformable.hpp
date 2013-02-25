/**
 * @file Transformable.hpp
 * @author Gruppe 2
 */

#ifndef TRANSFORMABLE_HPP_
#define TRANSFORMABLE_HPP_

#include "Renderable.hpp"

#include "math/Quaternion.hpp"
#include "math/glVector.hpp"

/**
 * @brief Base class for all objects that can be transformed, i.e. moved and rotated.
 */
class Transformable : public Renderable
{
    public:
        /**
         * @brief Ctor
         */
        Transformable();

        /**
         * @brief Dtor
         */
        virtual ~Transformable();

        /**
         * @brief   Rotates a triangle mesh at the given axis with the given speed
         * @param axis axis to rotate
         * @param speed speed of rotation
         */
        void rotate(int axis, float speed);

        /**
         * @brief   Moves a triangle mesh at the given axis with the given speed
         * @param axis axis to move
         * @param speed speed of movement
         */
        void move(int axis, float speed);

        /**
         * @brief   Renders the object.
         */
        virtual void render() = 0;

    protected:
        /**
         * @brief Computes the 4x4 transformation matrix of this object (needed for OpenGL)
         */
        void computeMatrix();

        // transformation matrix for this object
        float m_transformation[16];

        // current orientation of x-axis, y-axis and z-axis
        glVector<float> m_xAxis, m_yAxis, m_zAxis;

        // current position
        glVector<float> m_position;

        // current rotation
        Quaternion<float> m_rotation;
};

#endif /* Transformable.hpp */
