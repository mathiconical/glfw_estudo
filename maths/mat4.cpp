#define _USE_MATH_DEFINES

#include <math.h>
#include "mat4.h"

mat4::mat4()
{
	for (int i{ 0 }; i < 4 * 4; i++)
		elements[i] = 0.0f;
}

mat4::mat4(float diagonal)
{
	//! i == ( b * s ) - 1
	int j{ 0 }, k{ 0 };
	for (int i{ 0 }; i < 4 * 4; i++) {
		if (i == (4 * j + k)) {
			elements[i] = 1;
			++j; ++k;
		}
		else
			elements[i] = 0;
	}
}

mat4 mat4::identity()
{
	return mat4(1.0f);
}

//! a ordem da multiplicacao de matrizes segue a ordem que o
//! openGl usa, MCO (major column order).
mat4& mat4::multiply(const mat4& rhs)
{
	for (int j{ 0 }; j < 4; j++) 
	{
		for (int i{ 0 }; i < 4; i++)
		{
			float res = 0.0f;
			for (int k{ 0 }; k < 4; k++)
			{
				//! coluna * linha
				res += elements[i + k * 4] * rhs.elements[k + j * 4];
			}
			elements[i + j * 4] = res;
		}
	}
}

mat4 operator*(mat4 lhs, const mat4& rhs)
{
	mat4 r = lhs.multiply(rhs);
	return r;
}

mat4& mat4::operator*=(const mat4& rhs)
{
	return multiply(rhs);
}

mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	/* ORTHO MATRIX
	* r-l : right - left
	* t-p : top   - bottom
	* f-n : far   - near
	*
	* | 2/r-l   0       0    r+l/r-l |
	* |   0   2/t-b     0    t+b/t-b |
	* |   0     0    -2/f-n  f+n/f-n |
	* |   0     0       0       1    |
	*/
	mat4 r(1.0f);

	r.elements[0 + 0 * 4] = 2.0f / (right - left);
	r.elements[1 + 1 * 4] = 2.0f / (top - bottom);
	r.elements[2 + 2 * 4] = 2.0f / (far - near);

	r.elements[0 + 3 * 4] = (right + left) / (right - left);
	r.elements[1 + 3 * 4] = (top + bottom) / (top - bottom);
	r.elements[2 + 3 * 4] = (far + near) / (far - near);

	return r;
}

float toRadians(float deg)
{
	return deg * (M_PI / 180.0f);
}

mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
{
	/* PERSP MATRIX
	* fov : field of view
	* ar  : aspect ratio
	* f   : far
	* n   : near
	*
	* | 1/ar*tan(fov/2)        0                    0                        0
	* |        0         1 / (tan(fov/2)            0                        0
	* |        0               0          -(far+near/far-near)    -(2*far*near/far-near)
	* |        0               0                   -1                        0
	*/
	mat4 r(1.0f);

	float tan_fov = 1.0f / tan(toRadians(0.05f * fov)); // tan(fov/2)
	float aspec = tan_fov / aspectRatio;

	float near_far_1 = (near + far) / (near - far);
	float near_far_2 = (-(2 * far * near)) / (far - near);

	r.elements[0 + 0 * 4] = aspectRatio;
	r.elements[1 + 1 * 4] = tan_fov;
	r.elements[2 + 2 * 4] = near_far_1;
	r.elements[2 + 3 * 4] = near_far_2;
	r.elements[3 + 2 * 4] = -1.0f;

	return r;
}

mat4 mat4::translation(const vec3& translation)
{
	/* TRANS MATRIX
	* | 1 0 0 x |
	* | 0 1 0 y |
	* | 0 0 1 z |
	* | 0 0 0 1 |
	*/
	mat4 r(1.0f);

	r.elements[0 + 3 * 4] = translation.x;
	r.elements[1 + 3 * 4] = translation.y;
	r.elements[2 + 3 * 4] = translation.z;

	return r;
}


mat4 mat4::rotation(float angle, const vec3& axis)
{
	mat4 result(1.0f);

	float r = toRadians(angle);
	float c = cos(r);
	float s = sin(r);

	//! https://slidetodoc.com/arcball-interface-flavia-r-cavalcanti-definition-goal-implementation/
	// p'(p) = (cosO) P + (1 - cosO) (ê - p) ê + (sinO) * (ê * p)

	result.elements[0 + 0 * 4] = c + (1 - c) * axis.x;
	result.elements[1 + 0 * 4] = axis.y * axis.x * (1 - c) - axis.z * s;
	result.elements[2 + 0 * 4] = axis.z * axis.x * (1 - c) + axis.y * s;

	result.elements[0 + 1 * 4] = axis.x * axis.y * (1 - c) + axis.z * s;
	result.elements[1 + 1 * 4] = c + (1 - c) * axis.y * axis.y;
	result.elements[2 + 1 * 4] = axis.x * axis.y * (1 - c) - axis.x * s;

	result.elements[0 + 2 * 4] = axis.x * axis.z * (1 - c) - axis.y * s;
	result.elements[1 + 2 * 4] = axis.y * axis.z * (1 - c) - axis.x * s;
	result.elements[2 + 2 * 4] = c + (1 - c) * axis.z * axis.z;

	return result;
}

mat4 mat4::scale(const vec3& scale)
{
	mat4 r(1.0f);

	r.elements[0 + 0 * 4] = scale.x;
	r.elements[1 + 1 * 4] = scale.y;
	r.elements[2 + 2 * 4] = scale.z;

	return r;
}