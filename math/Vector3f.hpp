/**
 *  @file Vector3f.hpp
 *
 *  @date 05.12.2011
 *  @author Thomas Wiemann
 */

#ifndef __VECTOR3F_HPP__
#define __VECTOR3F_HPP__

#include <iostream>
#include <cmath>

#include "Global.hpp"

/**
 * @brief   Vector representation with three floats for OpenGL
 *
 */
class Vector3f {

public:

	/**
	 * @brief   Construcs a default vector3f object
	 */
	Vector3f();

	/**
	 * @brief   Construcs a vector3f object with given values
	 * @param x x-value
	 * @param y y-value
	 * @param z z-value
	 */
	Vector3f(double x, double y, double z);

	/**
	 * @brief   Normalize a vector3f
	 */
	void normalize();
	
	/**
	 * @brief   Calculates the cross product
	 * @param vec second vector
	 * @return vector
	 */
	Vector3f cross(Vector3f vec);

	/**
	 * @brief   Calculates the distance between two vectors
         * @param vec second vector
	 * @return distance as float
	 */

	double dist(Vector3f vec);
  
	/**
	 * @brief   Defines the vector addition
	 * @param vec vector
	 * @return vector
	 */
	Vector3f operator+ (const Vector3f vec) const;

	/**
	 * @brief   Defines the vector subtraction
	 * @param vec vector
	 * @return vector
	 */
	Vector3f operator- (const Vector3f vec) const;

	/**
	 * @brief   Construcs the scalar multiplication
	 * @param scale scalar
	 * @return vector
	 */
	Vector3f operator* (const float scale) const;

	/**
	 * @brief   Defines the vector multiplication
	 * @param vec vector
	 * @return result (as a float)
	 */
	double  operator* (const Vector3f vec) const;

	/**
	 * @brief   Defines the access to a vector3f value
	 * @param index wanted value
	 * @return vectorentry (as a float)
	 */
	double operator[] (const int& index) const;

	/**
	 * @brief   Defines the fast notation of vector addition
	 * @param v vector
	 */
	void operator+= (Vector3f v);

	/**
	 * @brief   The three values of a vector
	 */
	double x, y, z;
};

#endif
