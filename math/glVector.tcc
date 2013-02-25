#include "glVector.hpp"
#include <stdio.h>
#include <cassert>

template<typename T>
glVector<T>::glVector()
{
	// Default values
	x = y = z = 0.0;
}

template<typename T>
glVector<T>::glVector(T _x, T _y, T _z)
{
	// Set the given values
	x = _x;
	y = _y;
	z = _z; 
}

template<typename T>
double glVector<T>::dist(const glVector vec) const
{
	double _x = (double) x, _y = (double)y, _z = (double)z;
	glVector dist = glVector(_x - vec.x, _y - vec.y, _z - vec.z);
	float mag = dist.x * dist.x + dist.y * dist.y + dist.z * dist.z;
	if (fabs(mag - 1.0) > TOLERANCE)
	{
		return sqrt(mag);
	}
	else
	{
		return 1.0;
	}
}

template<typename T>
glVector<T> glVector<T>::operator+(const glVector<T> vec) const
{
	// Add value to value
	T tx = x + vec.x;
	T ty = y + vec.y;
	T tz = z + vec.z;
	return glVector<T>(tx, ty, tz);
}

template<typename T>
glVector<T> glVector<T>::operator-(const glVector<T> vec) const
{
	// Subtract value from value
	T tx = x - vec.x;
	T ty = y - vec.y;
	T tz = z - vec.z;
	return glVector<T>(tx, ty, tz);
}

template<typename T>
T glVector<T>::operator[](const int &index) const
{
	assert(index < 3);
	
	// Get the wanted value
	if(index == 0)
	{
		return x;
	}

	if(index == 1)
	{
		return y;
	}

	if(index == 2)
	{
		return z;
	}

	return 0;
}

template<typename T>
T glVector<T>::operator*(const glVector<T> vec) const
{
  // Calculate the result
  return (x * vec.x + y * vec.y + z * vec.z); 
}

template<typename T>
glVector<T> glVector<T>::operator*(T scale) const
{
	// Calculate the result
	T tx = x * scale;
	T ty = y * scale;
	T tz = z * scale;
	return glVector<float>(tx, ty, tz);
}

template<typename T>
void glVector<T>::operator+=(glVector<T> v)
{
	// Add value to value
	x += v.x;
	y += v.y;
	z += v.z;
}

template<typename T>
bool glVector<T>::operator<(const glVector<T> vec) const
{
    if (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) < sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
bool glVector<T>::operator>(const glVector<T> vec) const
{
    if (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) > sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
