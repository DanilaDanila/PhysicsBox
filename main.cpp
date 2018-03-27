#include <iostream>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "PhysicsBox.hpp"
#include <cmath>
#define pi 3.1415

float rotation=0.0;
phbox::vec2 mPos;
phbox::figure f0;
phbox::figure f1;

void drawPoint(phbox::vec2 p)
{
	glBegin(GL_POINTS);
	glVertex2f(p.x, p.y);
	glEnd();
}

void drawLine(phbox::line_segment l)
{
	glBegin(GL_LINES);
	glVertex2f(l.getFirstPoint().x, l.getFirstPoint().y);
	glVertex2f(l.getSecondPoint().x, l.getSecondPoint().y);
	glEnd();
}

void drawFigure(phbox::figure f)
{
	phbox::line_segment lines[f.getVertexCount()];
	for(int i=0;i<f.getVertexCount()-1;i++)
		lines[i]=phbox::line_segment(f.getVertexPosition(i),f.getVertexPosition(i+1));
	lines[f.getVertexCount()-1]=phbox::line_segment(f.getVertexPosition(f.getVertexCount()-1),f.getVertexPosition(0));

	for(int i=0; i<f.getVertexCount(); i++)
		drawLine(lines[i]);
}

phbox::vec2 color;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0,0.0,0.0);
	drawPoint(f0.getPosition());
	glColor3f(1.0, 1.0, 1.0);
	rotation+=0.01;
	f0.setRotation(rotation);
	drawFigure(f0);

	f1.setPosition(mPos);
	f1.setRotation(-rotation/2.0);
	if(f1.intersects(f0)) glColor3f(1.0,0.0,0.0);
	drawFigure(f1);

	/*glColor3f(color.x,color.y,0.0);
	drawPoint(mPos);
	drawPoint(phbox::vec2(mPos.x-1,mPos.y));
	drawPoint(phbox::vec2(mPos.x+1,mPos.y));
	drawPoint(phbox::vec2(mPos.x,mPos.y-1));
	drawPoint(phbox::vec2(mPos.x,mPos.y+1));*/

	glutSwapBuffers();
}

void mouse(int x, int y)
{
	mPos=phbox::vec2(x-10.0,576-y+10.0);
}

int main(int argc, char **argv)
{
	color=phbox::vec2(1.0,0.0);
	f0.setVertexCount(4);
	f0.setVertex(0, phbox::vec2(0.0,0.0));
	f0.setVertex(1, phbox::vec2(100.0,0.0));
	f0.setVertex(2, phbox::vec2(100.0,50.0));
	f0.setVertex(3, phbox::vec2(0.0,50.0));
	f0.setPosition(phbox::vec2(300.0,300.0));
	f0.setOriginToCenter();

	f1.setVertexCount(3);
	f1.setVertex(0, phbox::vec2(-50.0, 0.0));
	f1.setVertex(1, phbox::vec2(0.0, 50.0));
	f1.setVertex(2, phbox::vec2(50.0, 0.0));
	f1.setPosition(phbox::vec2(600.0, 300.0));
	f1.setOriginToCenter();

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