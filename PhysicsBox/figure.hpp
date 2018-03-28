#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "vec.hpp"
#include "line.hpp"

namespace phbox
{
	class figure
	{
	private:

		int vertexes_count;
		vec2 *vertexes;

		vec2 position;
		vec2 origin;

		float rotation;

	public:
		figure();

		line_segment *getLines();

		void setVertexCount(int);

		int getVertexCount();

		void setVertex(int vertex_num, vec2 coordinates);

		vec2 getVertex(int vertex_num);

		vec2 getVertexPosition(int vertex_num);

		void setOrigin(vec2);

		void setOriginToCenter();

		vec2 getOrigin();

		vec2 getCenter();

		void setRotation(float);

		float getRotation();

		void setPosition(vec2);

		vec2 getPosition();

		bool isPointInside(vec2);

		bool intersects(figure);

		~figure();
	};
};

#endif