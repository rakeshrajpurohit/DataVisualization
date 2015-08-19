#include <iostream>
#include <GL/glut.h>
#include "Glyphus.h"
#include "ColorMap.h"
#include <math.h>

Glyphus::Glyphus(float startX, float startY)
{
	this->startX = startX;
	this->startY = startY;
	magnitude   = 10.0;
	angle       = 10.0;
	endX = startX + 10.0;
	endY = startY + 10.0;
}

Glyphus::~Glyphus(void)
{
	
}
		
void Glyphus::findDirection(float X, float Y)
{
	angle = atan2f(Y,X);
	X = X>0?X:-X;
	Y = Y>0?Y:-Y;
	color = getColor((X+Y)/20);
}

void Glyphus::DrawGlyphus()
{	
	endX = startX+magnitude*cos(angle);
	endY = startY+magnitude*sin(angle);
	glBegin(GL_LINES);
		glColor3f(color.red, color.green, color.blue);
		glVertex3f(startX, startY, 50.0f);
		glVertex3f(endX, endY , 50.0f);
	glEnd();
}

void Glyphus::DrawArrow(void)
{
	float x1 = startX+(magnitude-4.0)*cos(angle+0.2);
	float y1 = startY+(magnitude-4.0)*sin(angle+0.2);
	float x2 = startX+(magnitude-4.0)*cos(angle-0.2);
	float y2 = startY+(magnitude-4.0)*sin(angle-0.2);
	
	glBegin(GL_TRIANGLES);
			glColor3f(color.red, color.green, color.blue);
			glVertex3f(x1, y1, 50.0);
			glVertex3f(x2, y2, 50.0);
			glVertex3f(endX, endY, 50.0);
	glEnd();
}

float Glyphus::getAngle()
{
	return angle;
}
