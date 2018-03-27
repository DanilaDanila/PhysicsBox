#include "determinant.hpp"

namespace phbox
{
	int det2i(int a11, int a12, int a21, int a22) { return a11*a22-a12*a21; }

	float det2f(float a11, float a12, float a21, float a22) { return a11*a22-a12*a21; }

	int det3i(int a11, int a12, int a13, int a21, int a22, int a23, int a31, int a32, int a33)
	{
		return a11*a22*a33+a12*a23*a31+a21*a13*a32-a31*a22*a13-a21*a12*a33-a32*a11*a23;
	}

	float det3f(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33)
	{
		return a11*a22*a33+a12*a23*a31+a21*a13*a32-a31*a22*a13-a21*a12*a33-a32*a11*a23;
	}
}