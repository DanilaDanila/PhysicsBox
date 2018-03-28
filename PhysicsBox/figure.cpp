#include "figure.hpp"
#include <cmath>

namespace phbox
{
	figure::figure() { vertexes=NULL; rotation=0; position=origin=vec2(0.0,0.0); }

	line_segment *figure::getLines()
	{
		line_segment *lines=new line_segment[vertexes_count];

		for(int i=0;i<vertexes_count-1;i++)
			lines[i]=line_segment(this->getVertexPosition(i),this->getVertexPosition(i+1));
		lines[vertexes_count-1]=line_segment(this->getVertexPosition(vertexes_count-1),this->getVertexPosition(0));
		return lines;
	}

	void figure::setVertexCount(int count)
	{
		vertexes_count=count;
		vertexes=new vec2[vertexes_count];
	}

	int figure::getVertexCount() { return vertexes_count; }

	void figure::setVertex(int num, vec2 coords)
	{
		if(vertexes!=NULL) vertexes[num]=coords;
	}

	vec2 figure::getVertex(int num)
	{
		if(vertexes!=NULL) return vertexes[num];
		return vec2(0.0,0.0);
	}

	///////////////////////////////////////
	vec2 figure::getVertexPosition(int num)
	{
		if(vertexes!=NULL)
		{
			vec2 vertex=vertexes[num];
			float x=origin.x+(vertex.x-origin.x)*cos(rotation)-(vertex.y-origin.y)*sin(rotation);
			float y=origin.y+(vertex.y-origin.y)*cos(rotation)+(vertex.x-origin.x)*sin(rotation);
			return vec2(x,y)+position-origin;
		}
		return vec2(0.0,0.0);
	}

	void figure::setOrigin(vec2 v) { origin=v; }

	vec2 figure::getCenter()
	{
		vec2 center(0.0,0.0);
		if(vertexes!=NULL)
		{
			for(int i=0;i<vertexes_count;i++) center=center+vertexes[i];
			center=center/vertexes_count;
		}

		return center;
	}

	void figure::setOriginToCenter()
	{
		if(vertexes!=NULL)
		{
			origin=vec2(0.0,0.0);
			for(int i=0;i<vertexes_count;i++) origin=origin+vertexes[i];
			origin=origin/vertexes_count;
		}
	}

	vec2 figure::getOrigin() { return origin; }

	void figure::setRotation(float angle) { rotation=angle; }

	float figure::getRotation() { return rotation; }

	void figure::setPosition(vec2 pos) { position=pos; }

	vec2 figure::getPosition() { return position; }

	bool figure::isPointInside(vec2 point)
	{
		bool check=false;
		if(vertexes!=NULL)
		{
			line_segment sides[vertexes_count];
			for(int i=0;i<vertexes_count-1;i++) sides[i]=line_segment(this->getVertexPosition(i),this->getVertexPosition(i+1));
			sides[vertexes_count-1]=line_segment(this->getVertexPosition(vertexes_count-1),this->getVertexPosition(0));

			check=true;
			vec2 middle=this->getCenter()+position-origin;
			for(int i=0;i<vertexes_count;i++)
			{
				check=sides[i].isPointsOnSameSide(point, middle);
				if(!check) break;
			}
		}
		return check;
	}

	bool figure::intersects(figure f)
	{
		// Some code

		line_segment *lines0=this->getLines();
		line_segment *lines1=f.getLines();

		for(int i=0;i<vertexes_count;i++)
			for(int j=0;j<f.getVertexCount();j++)
				if(lines0[i].intersects(lines1[j])) return true;

		return false;
	}

	figure::~figure() {}
};