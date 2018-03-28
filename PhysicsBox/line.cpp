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

	bool line_segment::intersects(line_segment l)
	{
		float D=det2f(A,B,l.getA(),l.getB());
		float Dx=det2f(-C,B,-l.getC(),l.getB());
		float Dy=det2f(A,-C,l.getA(),-l.getC());

		if(D!=0)
		{
			float l0x1=p0.x;
			float l0x2=p1.x;
			float l0y1=p0.y;
			float l0y2=p1.y;

			float l0left_border=(l0x1<l0x2)?l0x1:l0x2;
			float l0right_border=(l0x1>l0x2)?l0x1:l0x2;
			float l0up_border=(l0y1<l0y2)?l0y1:l0y2;
			float l0down_border=(l0y1>l0y2)?l0y1:l0y2;


			float l1x1=l.getFirstPoint().x;
			float l1x2=l.getSecondPoint().x;
			float l1y1=l.getFirstPoint().y;
			float l1y2=l.getSecondPoint().y;

			float l1left_border=(l1x1<l1x2)?l1x1:l1x2;
			float l1right_border=(l1x1>l1x2)?l1x1:l1x2;
			float l1up_border=(l1y1<l1y2)?l1y1:l1y2;
			float l1down_border=(l1y1>l1y2)?l1y1:l1y2;

			vec2 point=vec2(Dx/D,Dy/D);
			return (point.x>=l0left_border) and (point.x<=l0right_border) and (point.y>=l0up_border) and (point.y<=l0down_border) and
			       (point.x>=l1left_border) and (point.x<=l1right_border) and (point.y>=l1up_border) and (point.y<=l1down_border);
		}
		else return (D==0) and (Dx==0) and (Dy==0);
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