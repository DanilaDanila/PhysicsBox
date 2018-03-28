#ifndef LINE_HPP
#define LINE_HPP

#include "vec.hpp"
#include "determinant.hpp"

namespace phbox
{
	class line_segment
	{
	private:
		vec2 p0;
		vec2 p1;

		float A,B,C;

		void countABC();

	public:
		line_segment();

		line_segment(vec2 p0, vec2 p1);

		float getA();

		float getB();

		float getC();

		void setFirstPoint(vec2);

		void setSecondPoint(vec2);

		vec2 getFirstPoint();

		vec2 getSecondPoint();

		vec2 getMiddle();

		float getLength();

		vec2 getNormalFromPoint(vec2);

		vec2 getIntersectionWithLine(line_segment);

		float getDistanceFromPoint(vec2);

		bool intersects(line_segment);

		bool isPointOn(vec2);

		bool isPointsOnSameSide(vec2, vec2);

		~line_segment();
	};
};

#endif