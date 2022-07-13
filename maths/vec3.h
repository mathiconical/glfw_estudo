#pragma once

struct vec3 {
	float x, y, z;

	vec3();
	vec3(const float& x, const float& y, const float& z);

	vec3& add(const vec3& rhs);
	vec3& subtract(const vec3& rhs);
	vec3& divide(const vec3& rhs);
	vec3& multiply(const vec3& rhs);

	friend vec3& operator+(vec3& lhs, const vec3& rhs);
	friend vec3& operator-(vec3& lhs, const vec3& rhs);
	friend vec3& operator*(vec3& lhs, const vec3& rhs);
	friend vec3& operator/(vec3& lhs, const vec3& rhs);

	vec3& operator+=(const vec3& rhs);
	vec3& operator-=(const vec3& rhs);
	vec3& operator*=(const vec3& rhs);
	vec3& operator/=(const vec3& rhs);

	bool operator==(const vec3& rhs);
	bool operator!=(const vec3& rhs);
};