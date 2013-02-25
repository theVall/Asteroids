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
template<typename T>
class glVector {

public:

	/**
	 * @brief   Construcs a default glVector object
	 */
	glVector();

	/**
	 * @brief   Construcs a glVector object with given values
	 * @param x x-value
	 * @param y y-value
	 * @param z z-value
	 */
	glVector(T _x, T _y, T _z);

	/**
	 * @brief distance to other vector
	 * @ param vec other vector
	 * @ return distance to other vector
	 */
	double dist(const glVector vec) const;


	/**
	 * @brief   Defines the vector addition
	 * @param vec vector
	 * @return vector
	 */
	glVector operator+ (const glVector vec) const;

	/**
	 * @brief   Defines the vector subtraction
	 * @param vec vector
	 * @return vector
	 */
	glVector operator- (const glVector vec) const;

	/**
	 * @brief   Construcs the scalar multiplication
	 * @param scale scalar
	 * @return vector
	 */
	glVector operator* (const T scale) const;

	/**
	 * @brief   Defines the vector multiplication
	 * @param vec vector
	 * @return result (as a T)
	 */
	T  operator* (const glVector vec) const;

	/**
	 * @brief   Defines the access to a glVector value
	 * @param index wanted value
	 * @return vectorentry (as a T)
	 */
	T operator[] (const int& index) const;

	/**
	 * @brief   Defines the fast notation of vector addition
	 * @param v vector
	 */
	void operator+= (glVector v);
    
    /**
     * @brief Defines notation of compare length of two vectors
     */
    bool operator< (glVector vec) const;

    /**
     * @brief Defines notation of compare length of two vectors
     */
    bool operator> (glVector vec) const;
    
	/**
	 * @brief   The three values of a vector
	 */
	T x, y, z;

};

#include "glVector.tcc"

#endif
