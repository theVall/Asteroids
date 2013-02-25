#include "Vector3f.hpp"
#include <stdio.h>
#include <cassert>

Vector3f::Vector3f()
{
	// Default values
	x = y = z = 0.0;
}


Vector3f::Vector3f(float _x, float _y, float _z)
{
	// Set the given values
	x = _x;
	y = _y;
	z = _z; 
}

void Vector3f::normalize()
{
	// Normalize the vector
	float mag2 = x * x + y * y + z * z;
	if (fabs(mag2 - 1.0f) > TOLERANCE)
	{
		float mag = sqrt(mag2);
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

Vector3f Vector3f::cross(Vector3f b)
{
  // Calculate the cross product
  float tx = y * b.z - z * b.y;
  float ty = z * b.x - x * b.z;
  float tz = x * b.y - y * b.x;

  return Vector3f(tx, ty, tz);  
}

float Vector3f::dist(Vector3f vec)
{

  // Calculate the distance
  Vector3f dist = Vector3f(x - vec.x, y - vec.y, z - vec.z);
  float mag = dist.x * dist.x + dist.y * dist.y + dist.z * dist.z;
  if (fabs(mag - 1.0f) > TOLERANCE)
  { 
	return sqrt(mag);
  }
  else
  {
	return 1.0f;
  }
}

Vector3f Vector3f::operator+(const Vector3f vec) const
{
	// Add value to value
	float tx = x + vec.x;
	float ty = y + vec.y;
	float tz = z + vec.z;
	return Vector3f(tx, ty, tz);
}

Vector3f Vector3f::operator-(const Vector3f vec) const
{
	// Subtract value from value
	float tx = x - vec.x;
	float ty = y - vec.y;
	float tz = z - vec.z;
	return Vector3f(tx, ty, tz);
}


float Vector3f::operator[](const int &index) const
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

float Vector3f::operator*(const Vector3f vec) const
{
  // Calculate the result
  return (x * vec.x + y * vec.y + z * vec.z); 
}

Vector3f Vector3f::operator*(float scale) const
{
	// Calculate the result
	float tx = x * scale;
	float ty = y * scale;
	float tz = z * scale;
	return Vector3f(tx, ty, tz);
}

void Vector3f::operator+=(Vector3f v)
{
	// Add value to value
	x += v.x;
	y += v.y;
	z += v.z;
}
