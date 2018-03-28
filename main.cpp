#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "PhysicsBox.hpp"
#include <cmath>

using namespace phbox;

vec2 mPos;
figure f0,f1;

void drawPoint(vec2 v)
{
	glBegin(GL_POINTS);
	glVertex2f(v.x,v.y);
	glEnd();
}

void drawLine(line_segment l)
{
	glBegin(GL_LINES);
	glVertex2f(l.getFirstPoint().x, l.getFirstPoint().y);
	glVertex2f(l.getSecondPoint().x, l.getSecondPoint().y);
	glEnd();
}

void drawFigure(figure f)
{
	line_segment *lines=f.getLines();

	for(int i=0;i<f.getVertexCount();i++)
		drawLine(lines[i]);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	f0.setRotation(f0.getRotation()+0.01);
	drawFigure(f0);

	if(f1.intersects(f0)) glColor3f(1.0, 0.0, 0.0);
	f1.setPosition(mPos);
	drawFigure(f1);

	glutSwapBuffers();
}

void mouse(int x, int y)
{
	mPos=phbox::vec2(x-10.0,576-y+10.0);
}

int main(int argc, char **argv)
{
	f0.setVertexCount(5);
	f0.setVertex(0, vec2(0.0, 0.0));
	f0.setVertex(1, vec2(0.0, 40.0));
	f0.setVertex(2, vec2(20.0, 60.0));
	f0.setVertex(3, vec2(40.0, 40.0));
	f0.setVertex(4, vec2(40.0, 0.0));
	f0.setOriginToCenter();
	f0.setPosition(vec2(300.0, 300.0));

	f1.setVertexCount(3);
	f1.setVertex(0, vec2(0.0, 0.0));
	f1.setVertex(1, vec2(40.0, 20.0));
	f1.setVertex(2, vec2(60.0, 0.0));
	f1.setOriginToCenter();
	f1.setPosition(vec2(500.0, 300.0));

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1024, 576);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("");

	gluOrtho2D(0.0, 1024.0, 0.0, 576.0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMotionFunc(mouse);
	glutPassiveMotionFunc(mouse);

	glutMainLoop();

	return 0;
}
