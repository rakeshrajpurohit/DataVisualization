/**
 * Author : Rakesh Rajpurohit
 * Mt2013122
 * Assignment-1
 */ 

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "EasyBMP.h"
#include "vec3f.h"
#include "elevation.h"
    
using namespace std;
BMP image;

float _angle = 60.0f;
Elevation* elevation;

//value for isoline for the contour mapping
int iso = 0;
int isoline[4] = {-205,-5, 0, 25};

//load the bmp image and store the values of intensity 
//and find out the value of height and color and compute normals
Elevation* loadImage(float height) {
	image.ReadFromFile("../images/GC.bmp");
	
	Elevation* t = new Elevation(image.TellWidth(), image.TellHeight());
	
	//set height and color value for elevation and color mapping
	for(int y = 0; y < image.TellHeight(); y++) {
		for(int x = 0; x < image.TellWidth(); x++) {
			unsigned char color = (unsigned char)image(x,y)->Red;
			float h = height * ((color / 255.0f) - 0.5f);
			t->setHeight(x, y, h);
			t->setColor(x, y, (color/255.0f));
		}
	}
	t->computeNormals();
	return t;
}

void cleanup() {
	delete elevation;
}

//Handle key pres for Escape key
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			cleanup();
			exit(0);
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

//Draw function 
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-_angle, 0.0f, 1.0f, 0.0f);
	
	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	float scale = 10.0f / max(elevation->width() - 1, elevation->length() - 1);
	glScalef(scale, scale, scale);
	glTranslatef(-(float)(elevation->width() - 1) / 2, 0.0f, -(float)(elevation->length() - 1) / 2);

	for(int z = 0; z < elevation->length() - 1; z++) {
		//draw a triangle at every three consecutive vertices
		glBegin(GL_TRIANGLE_STRIP);
		for(int x = 0; x < elevation->width(); x++) {
			
			Color colorValue = elevation->getColor(x, z);
			glColor3f(colorValue.red,colorValue.green ,colorValue.blue);

			Vec3f normal = elevation->getNormal(x, z);
			glNormal3f(normal[0], normal[1], normal[2]);
			glVertex3f(x, elevation->getHeight(x, z), z);
			
			normal = elevation->getNormal(x, z + 1);
			glNormal3f(normal[0], normal[1], normal[2]);
			glVertex3f(x, elevation->getHeight(x, z + 1), z + 1);
			
		}
		glEnd();
	}
	
	//Draw contour lines
	for(int i = 0; i< 4; i++){
		iso = isoline[i];
		glBegin(GL_LINES);
		for (int lat = 0; lat < elevation->length() - 1; ++lat) {
			for (int lon = 0; lon < elevation->width() - 1; ++lon) {
				//the isoline value at corner If greater then 1 else 0
				int bl = elevation->getHeight(lon, lat) >= iso;
				int br = elevation->getHeight(lon + 1, lat) >= iso;
				int tl = elevation->getHeight(lon, lat + 1) >= iso;
				int tr = elevation->getHeight(lon + 1, lat + 1) >= iso;
				
				//find out the index value
				int config = bl | (br << 1) | (tl << 2) | (tr << 3);
				
				//Remove the redundant cases
				if (config > 7) {
					config = 15 - config;
				}
				
				//Draw the line based on the case of marching square
				Vec3f normal = elevation->getNormal(lon, lat);
				glNormal3f(normal[0], normal[1], normal[2]);
				glColor3f(1.0, 1.0, 1.0);
				switch (config) {
				case 0:
				break;
				case 1:
				glVertex3f(lon, elevation->getHeight(lon, lat), lat+0.5f);
				glVertex3f(lon+0.5f, elevation->getHeight(lon, lat), lat+0.5f);
				break;
				case 2:
				glVertex3f(lon + 0.5f,elevation->getHeight(lon, lat), lat);
				glVertex3f(lon + 1.0f,elevation->getHeight(lon, lat), lat + 0.5f);
				break;
				case 3:
				glVertex3f(lon, elevation->getHeight(lon, lat), lat + 0.5f);
				glVertex3f(lon + 1.0f, elevation->getHeight(lon, lat), lat + 0.5f);
				break;
				case 4:
				glVertex3f(lon, elevation->getHeight(lon, lat), lat + 0.5f);
				glVertex3f(lon + 0.5f, elevation->getHeight(lon, lat), lat + 1.0f);
				break;
				case 5:
				glVertex3f(lon + 0.5f, elevation->getHeight(lon, lat), lat);
				glVertex3f(lon + 0.5f, elevation->getHeight(lon, lat), lat + 1.0f);
				break;
				case 6:
				glVertex3f(lon + 0.5f, elevation->getHeight(lon, lat), lat);
				glVertex3f(lon, elevation->getHeight(lon, lat), lat + 0.5f);
				glVertex3f(lon + 0.5f, elevation->getHeight(lon, lat), lat + 1.0f);
				glVertex3f(lon + 1.0f, elevation->getHeight(lon, lat), lat + 0.5f);
				break;
				case 7:
				glVertex3f(lon + 0.5f, elevation->getHeight(lon, lat), lat + 1.0f);
				glVertex3f(lon + 1.0f, elevation->getHeight(lon, lat), lat + 0.5f);
				break;
				}
			}
		}
		glEnd();
	}
	glutSwapBuffers();
}

void update(int value) {
	_angle += 1.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	
	glutPostRedisplay();
	glutTimerFunc(15, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 700);	
	glutCreateWindow("MT2013122_Assignment1 ");
	initRendering();
	elevation = loadImage(700);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(15, update, 0);
	
	glutMainLoop();
	return 0;
}
