#include "line.hpp"
#include <cmath>

namespace phbox
{
	void line_segment::countABC()
	{
		A=p0.y-p1.y;
		B=p1.x-p0.x;
		C=p0.x*p1.y-p1.x*p0.y;
	}

	line_segment::line_segment() {}

	line_segment::line_segment(vec2 v0, vec2 v1): p0(v0), p1(v1) { countABC(); }

	float line_segment::getA() { return A; }

	float line_segment::getB() { return B; }

	float line_segment::getC() { return C; }

	void line_segment::setFirstPoint(vec2 v) { p0=v; countABC(); }

	void line_segment::setSecondPoint(vec2 v) { p1=v; countABC(); }

	vec2 line_segment::getFirstPoint() { return p0; }

	vec2 line_segment::getSecondPoint() { return p1; }

	vec2 line_segment::getMiddle() { return (p1-p0)/2; }

	float line_segment::getLength() { return sqrt((p1.x-p0.x)*(p1.x-p0.x)+(p1.y-p0.y)*(p1.y-p0.y)); }

	vec2 line_segment::getNormalFromPoint(vec2 point)
	{
		// A(y-y1)-B(x-x1)=0 <=> -Bx+Ay+(Bx1-Ay1)=0
		float A1,B1,C1;
		A1=-B;
		B1=A;
		C1=B*point.x-A*point.y;

		float D=det2f(A,B,A1,B1);
		float Dx=det2f(-C,B,-C1,B1);
		float Dy=det2f(A,-C,A1,-C1);

		if(D!=0) return vec2(Dx/D-point.x,Dy/D-point.y);
		return vec2();
	}

	vec2 line_segment::getIntersectionWithLine(line_segment l)
	{
		float D=det2f(A,B,l.getA(),l.getB());
		float Dx=det2f(-C,B,-l.getC(),l.getB());
		float Dy=det2f(A,-C,l.getA(),-l.getC());

		return vec2(Dx/D,Dy/D);
	}

	float line_segment::getDistanceFromPoint(vec2 point) { return getNormalFromPoint(point).module(); }

	bool line_segment::checkIntersectionWithLine(line_segment l)
	{
		float D=det2f(A,B,l.getA(),l.getB());
		float Dx=det2f(-C,B,-l.getC(),l.getB());
		float Dy=det2f(A,-C,l.getA(),-l.getC());

		if(D!=0)
		{
			float x0=l.getFirstPoint().x;
			float x1=l.getSecondPoint().x;
			float y0=l.getFirstPoint().y;
			float y1=l.getSecondPoint().y;

			float left_border=(x0<x1)?x0:x1;
			float right_border=(x0<x1)?x1:x0;
			float up_border=(y0<y1)?y0:y1;
			float down_border=(y0<y1)?y1:y0;

			return ((Dx/D>=left_border) && (Dx/D<=right_border) && (Dy/D>=up_border) && (Dy/D<=down_border));
		}
		else
		if(D==Dx==Dy==0) return true;
		else return false;
	}

	bool line_segment::isPointOn(vec2 point)
	{
		return (this->getDistanceFromPoint(point)==0) and (distance(this->getNormalFromPoint(point)+point,this->getMiddle())<=this->getLength()/2.0);
	}

	bool line_segment::isPointsOnSameSide(vec2 v0, vec2 v1)
	{
		return (this->getNormalFromPoint(v0)*this->getNormalFromPoint(v1))>=0;
	}

	line_segment::~line_segment() {}
};