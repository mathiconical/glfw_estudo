#include "vec3.h"

vec3::vec3()
	: x(0), y(0), z(0)
{
}

vec3::vec3(const float& x, const float& y, const float& z)
	: x(x), y(y), z(z)
{
}

vec3& vec3::add(const vec3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

vec3& vec3::subtract(const vec3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

vec3& vec3::multiply(const vec3& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

vec3& vec3::divide(const vec3& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}

vec3& operator+(vec3& lhs, const vec3& rhs)
{
	return lhs.add(rhs);
}

vec3& operator-(vec3& lhs, const vec3& rhs)
{
	return lhs.subtract(lhs);
}

vec3& operator*(vec3& lhs, const vec3& rhs)
{
	return lhs.multiply(rhs);
}

vec3& operator/(vec3& lhs, const vec3& rhs)
{
	return lhs.divide(rhs);
}

vec3& vec3::operator+=(const vec3& rhs)
{
	return add(rhs);
}

vec3& vec3::operator-=(const vec3& rhs)
{
	return subtract(rhs);
}

vec3& vec3::operator/=(const vec3& rhs)
{
	return divide(rhs);
}

vec3& vec3::operator*=(const vec3& rhs)
{
	return multiply(rhs);
}

bool vec3::operator==(const vec3& rhs)
{
	return x == rhs.x && y == rhs.y;
}

bool vec3::operator!=(const vec3& rhs)
{
	return !(*this == rhs);
}