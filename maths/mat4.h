#pragma once

#include "vec3.h"

struct mat4 {
	float elements[4 * 4];

	mat4();
	mat4(diagonal);

	static mat4 identity();

	mat4& multiply();

	mat4& operator*=(const mat4& rhs);
	friend mat4 operator*(mat4 lhs, const mat4& rhs);

	static mat4 ortographic(float left, float down, float right, float top, float near, float far);
	static mat4 perspective(float fov, float aspectRatio, float near, float far);

	static mat4 translation(const vec3& translation);
	static mat4 rotation(float angle, const vec3& axis);
	static mat4 scale(const vec3& scale);
};