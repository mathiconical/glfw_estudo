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