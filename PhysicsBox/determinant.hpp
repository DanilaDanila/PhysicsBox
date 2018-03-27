#ifndef DETERMINANT_HPP
#define DETERMINANT_HPP

namespace phbox
{
	int det2i(int a11, int a12, int a21, int a22);

	float det2f(float a11, float a12, float a21, float a22);

	int det3i(int a11, int a12, int a13, int a21, int a22, int a23, int a31, int a32, int a33);

	float det3f(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33);
};

#endif