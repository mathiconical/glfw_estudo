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