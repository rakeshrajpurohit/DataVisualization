#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include "floatData.h"
#include "Glyphus.h"
#include "ColorMap.h"
#include <stdlib.h>
#include <time.h>
#include "LIC.h"
using namespace std;

//constants related to lightning
float light_diffuse[] = {2.0, 2.0, 1.0, 1.0}; 
float light_position[] = {10.0, 5.0, 5.0, 0.0};
//Data object
floatData FD;

//Object intialization for line integral convolution
LIC LC = LIC();

//function for Hedgehog visualization 
// Here the sum of wind speed in X and Y direction taken then normalized
// to represent them.
void drawGlyphViz(int i)
{
	float resultX = 0.0, resultY = 0.0;
	for(int j =0; j<500; j++)
	{
		if(j%15 == 0  && i%15 == 0)
		{	Glyphus G = Glyphus(i,j);
			G.findDirection(resultX/15.0, resultY/15.0);
			G.DrawGlyphus();
			G.DrawArrow();
			resultX = 0.0;
			resultY = 0.0;
		}
		else{
			resultX += FD.getDataX(i, j, 20);
			resultY += FD.getDataY(i, j, 20);
		}
	} 
}

//Function to draw the curve tangent to the vector field using euiler method.
void drawApproximation(float initX, float initY, float deltaX){
	float x = initX;
	float y = initY;
	while ((x<500) && (y<500)) 
	{	
		float X = FD.getDataY(x, y, 60);
		float Y = FD.getDataX(x, y, 60);
		float slope = sin(atan2f(Y, X));
		float xNext = x + deltaX;
		float yNext = y + slope*deltaX;
		X = X>0?X:-X; 
		Y = Y>0?Y:-Y;
		Color color = getColor((X+Y)/40);
		glBegin(GL_LINES);
			glColor3f(color.red, color.green, color.blue);
			glVertex3f(x, y, 50.0f);
			glVertex3f(xNext, yNext, 50.0f);
		glEnd();
		x = xNext;
		y = yNext;
	}
}	

//Function to implement the Line Integral Convolution.
void drawLIC()
{
	int	xSize = 500; //Width of LIC
	int	ySize = 500; //Height of LIC
	
	//Allocate memory for various parameters
	float*	vectr = (float*) malloc(sizeof(float)*xSize*ySize*2 );
	float*	lut0  = (float*) malloc(sizeof(float)*2048.0f);
	float*	lut1  = (float*) malloc(sizeof(float)*2048.0f);
	unsigned char*	noise = (unsigned char* ) malloc( sizeof(unsigned char) * xSize * ySize );
	unsigned char*	licArray = (unsigned char* ) malloc( sizeof(unsigned char) * xSize * ySize );
	
	LC.vectorField(xSize, ySize, vectr);  //find out vector field
	LC.NormalizVectrs(xSize, ySize, vectr); //Normalize the vector field
	LC.MakeNoise(xSize, ySize, noise);     //Generate the Noise 
	LC.GenBoxFiltrLUT(2048.0f , lut0, lut1); 
	LC.FlowImagingLIC(xSize, ySize, vectr, noise, licArray, lut0, lut1, 10.0f);
	LC.displayLIC(xSize, ySize,  licArray);

	free(vectr);
	free(lut0);		
	free(lut1);	
	free(noise);	
	free(licArray);	
		
	vectr = NULL;
	lut0 = NULL;
	lut1 = NULL;
	noise = NULL;
	licArray = NULL;
}

//Draw function 
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -15.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	
	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	float scale = 10.0f / 500.0;
	glScalef(scale, scale, scale);
	glTranslatef(-250.0f, -250.0f, -300.0f);
		
}

//Handle key press for Escape key
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;
		
		case 'w'://Draw Vector Glyphus
				drawScene();
			for(int i = 0; i<500; i++)			
				drawGlyphViz(i);	
			glutSwapBuffers();
			break;
			
		case 's'://DrawStreamLines
				drawScene();
			for(int i=0; i<500; i = i+30)
				for(int j = 0;j<500; j = j+30)
					drawApproximation(i, j, 1.0);		
			glutSwapBuffers();
			break;
		
		case 'd'://Draw LIC
				drawScene();
			drawLIC();		
			glutSwapBuffers();
			break;
	}
	 
}

//Initial tendering function
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

//Resize function to handle the resize of window
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);	
	glutCreateWindow("MT2013122_Assignment2 ");
	initRendering();
	FD.loadFiles();
	FD.convertEndian(); 
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	return 0;
}
