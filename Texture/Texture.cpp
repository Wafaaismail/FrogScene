
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"


using namespace std;

/***********************Variables*****************************************/
Image* image;
GLuint _texturegrass; //The id of the grass texture
GLuint _texturewater; //The id of the water texture
GLuint _texturerock; //The id of the  wall texture
GLuint _texturesky; //The id of the sky texture
GLuint _textureland; //The id of the land texture

/***********************Prototypes*****************************************/
void renderSky();
void renderwater();
void renderGrass();
void renderwall();
void renderland();


void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}



void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	//grass img assign 
	image = loadBMP("grass.bmp");
	_texturegrass = loadTexture(image);
	//water img assign
	image = loadBMP("water.bmp");
	_texturewater = loadTexture(image);
	
	//rock img assign
	image = loadBMP("wall.bmp");
	_texturerock = loadTexture(image);
	
	//sky img assign
	image = loadBMP("sky3.bmp");
	_texturesky = loadTexture(image);
	
	//land img assign
	image = loadBMP("land.bmp");
	_textureland = loadTexture(image);
	delete image;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat ambientLight[] = { 1.f, 1.f, 1.f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat directedLightPos[] = { -0.0f, 15.0f, 20.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	
	glPushMatrix();
	renderGrass();
	glPopMatrix();
	
	glPushMatrix();
	renderwater();
	glPopMatrix();
	
	glPushMatrix();
	renderwall();
	glPopMatrix();

	glPushMatrix();
	renderSky();
	glPopMatrix();

	glPushMatrix();
	renderland();
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Frog Scene using Texture");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop();
	return 0;
}

void renderSky() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texturesky);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0., 0.);
	glVertex3f(-5.f, 0.6f, -6.5f);

	glTexCoord2f(1., 0.);
	glVertex3f(5.f, 0.6f, -6.5f);

	glTexCoord2f(1., 1.);
	glVertex3f(5.f, 3.6f, -6.5f);

	glTexCoord2f(0., 1.);
	glVertex3f(-5.f, 3.6f, -6.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}


void renderGrass() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texturegrass);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
	glEnable(GL_TEXTURE_2D);
	glVertex3f(-0.1, -1.0, -5.3);
	glTexCoord2f(1., 3.);

	glVertex3f(-2.85, -1.0, -5.3);
	glTexCoord2f(1, 2.0);

	glVertex3f(-2.85, -1.3, -5.0);
	glTexCoord2f(2., 1.);
	glVertex3f(0.0, -1.3, -5.0);
	glTexCoord2f(0, 2.0);

	//second green rec
	glColor3f(0.0, 1.0, 0.0);


	glVertex3f(1., -.3, -5.6);
	glTexCoord2f(0., 0.);


	glVertex3f(1.5, -.3, -5.6);
	glTexCoord2f(1, 0.0);

	glVertex3f(1.8, -1.3, -5.0);
	glTexCoord2f(1., 1.);

	glVertex3f(1.3, -1.3, -5.0);
	glTexCoord2f(0., 1.);
	/*************************************************/
	glColor3f(0.0, 1.0, 0.0);

	glTexCoord2f(0., 0.);
	glVertex3f(-2.7, -.3, -5.6);

	glTexCoord2f(1., 0.);
	glVertex3f(1.5, -.3, -5.6);

	glTexCoord2f(1., 1.);
	glVertex3f(1.4, 0, -5.9);

	glTexCoord2f(0., 1.);
	glVertex3f(-2.7, 0, -5.9);
	/********************************************************/

	glTexCoord2f(0., 0.);
	glVertex3f(-2.7, 0.3, -6.2);

	glTexCoord2f(1., 0.);
	glVertex3f(1.3, 0.3, -6.2);

	glTexCoord2f(1., 1.);
	glVertex3f(1.25, 0.4, -6.3);

	glTexCoord2f(0., 1.);
	glVertex3f(-2.7, 0.4, -6.3);



	/****************************/

	glTexCoord2f(0., 0.);
	glVertex3f(-2.7, 0.4, -6.3);

	glTexCoord2f(1., 0.);
	glVertex3f(-2.5, 0.4, -6.3);

	glTexCoord2f(1., 1.);
	glVertex3f(-2.2, 0.6, -6.5);

	glTexCoord2f(0., 1.);
	glVertex3f(-2.6, 0.6, -6.5);


	/***************************************************************/
	glTexCoord2f(0., 0.);
	glVertex3f(0.3, 0.4, -6.3);

	glTexCoord2f(1., 0.);
	glVertex3f(2.1, 0.4, -6.3);

	glTexCoord2f(1., 1.);
	glVertex3f(2.03, 0.6, -6.5);

	glTexCoord2f(0., 1.);
	glVertex3f(0.25, 0.6, -6.5);

	glEnd();
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0., 0.);
	glVertex3f(2.4, 0.25, -6.15);
	glTexCoord2f(1., 0.);
	glVertex3f(2.4, -1.3, -5.0);
	glTexCoord2f(1., 1.);
	glTexCoord2f(0., 1.);
	glVertex3f(1.9, 0.25, -6.15);

	glEnd();

	glDisable(GL_TEXTURE_2D);

}
void renderwater() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texturewater);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor3f(255 / 255, 255 / 255, 255 / 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0., 0.);
	glVertex3f(-2.85, -1, -5.3);

	glTexCoord2f(1., 0.);
	glVertex3f(-0.1, -1, -5.3);

	glTexCoord2f(1., 1.);
	glVertex3f(-0.35, -0.3, -5.6);

	glTexCoord2f(0., 1.);
	glVertex3f(-2.7, -0.3, -5.6);

	/******************************************************/
	glTexCoord2f(0., 0.);
	glVertex3f(-2.7, 0, -5.9);

	glTexCoord2f(1., 0.);
	glVertex3f(1.4, 0, -5.9);

	glTexCoord2f(1., 1.);
	glVertex3f(1.3, 0.3, -5.6);

	glTexCoord2f(0., 1.);
	glVertex3f(-2.7, 0.3, -6.2);

	/*******************************************************************************/
	glTexCoord2f(0., 0.);
	glVertex3f(1.8, -1.3, -5.0);

	glTexCoord2f(1., 0.);
	glVertex3f(2.4, -1.3, -5.0);
	glTexCoord2f(1., 1.);
	glVertex3f(1.9, 0.4, -6.3);
	glTexCoord2f(0., 1.);
	glVertex3f(1.25, 0.4, -6.3);
	/********************************************************/
	glTexCoord2f(0., 0.);
	glVertex3f(1.8, 0.25, -6.15);

	glTexCoord2f(1., 0.);
	glVertex3f(2.4, 0.25, -6.15);

	glTexCoord2f(1., 1.);
	glVertex3f(2.4, 0.4, -6.3);

	glTexCoord2f(0., 1.);
	glVertex3f(1.9, 0.4, -6.3);


	/********************************************************/
	glTexCoord2f(0., 0.);
	glVertex3f(-2.6, 0.4, -6.3);

	glTexCoord2f(1., 0.);
	glVertex3f(-2.2, 0.4, -6.3);

	glTexCoord2f(1., 1.);
	glVertex3f(-1.65, 0.6, -6.5);

	glTexCoord2f(0., 1.);
	glVertex3f(-2.3, 0.6, -6.5);

	/********************************************************************/
	glTexCoord2f(0., 0.);
	glVertex3f(-2.4, 0.4, -6.3);

	glTexCoord2f(1., 0.);
	glVertex3f(0.3, 0.4, -6.3);

	glTexCoord2f(1., 1.);
	glVertex3f(0.25, 0.6, -6.5);

	glTexCoord2f(0., 1.);
	glVertex3f(-2., 0.6, -6.5);
	/***************************************************************/
	glTexCoord2f(0., 0.);
	glVertex3f(2.1, 0.4, -6.3);

	glTexCoord2f(1., 0.);
	glVertex3f(2.4, 0.4, -6.3);

	glTexCoord2f(1., 1.);
	glVertex3f(2.4, 0.6, -6.5);

	glTexCoord2f(0., 1.);
	glVertex3f(2, 0.6, -6.5);


	glTexCoord2f(0., 0.);
	glVertex3f(0.0, -1.3, -5.0);

	glTexCoord2f(1., 0.);
	glVertex3f(1.3, -1.3, -5.0);

	glTexCoord2f(1., 1.);
	glVertex3f(1, -0.3, -5.6);

	glTexCoord2f(0., 1.);
	glVertex3f(-0.35, -0.3, -5.6);


	glEnd();
	glDisable(GL_TEXTURE_2D);


}
void renderwall() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texturerock);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//right wall
	glBegin(GL_QUADS);
	//bottom
	glVertex3f(2.4, -1.3, -5);
	glTexCoord2f(0., 0.);

	glVertex3f(4.4, -1.3, -5);
	glTexCoord2f(1., 0.);

	glVertex3f(5, 0.6, -6.5);
	glTexCoord2f(1., 1.);

	glVertex3f(2.4, 0.6, -6.5);
	glTexCoord2f(0., 1.);

	//top
	glTexCoord2f(0., 0.);
	glVertex3f(2.4f, 1.6f, -6.5f);
	glTexCoord2f(1., 0.);

	glVertex3f(5.f, 1.6f, -6.5f);
	glTexCoord2f(1., 1.);
	glVertex3f(5.f, -0.3f, -5.f);


	glTexCoord2f(0., 1.);
	glVertex3f(2.4f, -0.3f, -5.f);
	glTexCoord2f(0., 0.);

	// Front face  (z = 1.0f)

	glTexCoord2f(0., 0.);
	glVertex3f(5.f, -0.3f, -5.f);

	glTexCoord2f(1., 0.);
	glVertex3f(2.4f, -0.3f, -5.f);

	glTexCoord2f(1., 1.);
	glVertex3f(2.4f, -1.3f, -5.0f);

	glTexCoord2f(0., 1.);
	glVertex3f(5.f, -1.3f, -5.0f);


	// Left face (x = -1.0f)

	glTexCoord2f(0., 0.);
	glVertex3f(2.4f, -1.3f, -5.0f);
	
	glVertex3f(2.4f, 0.6f, -6.5f);
	glTexCoord2f(1., 0.);

	glVertex3f(2.4f, 1.6f, -6.5f);
	glTexCoord2f(1., 1.);

	glVertex3f(2.4f, -0.3f, -5.f);
	glTexCoord2f(0., 1.);
	glEnd();

	/**********************************************************/
	//left wall
	glBegin(GL_QUADS);

	//top 
	glTexCoord2f(0., 0.);
	glVertex3f(-2.6f, 1.6f, -6.5f);

	glTexCoord2f(1., 0.);
	glVertex3f(-5.f, 1.6f, -6.5f);

	glTexCoord2f(1., 1.);
	glVertex3f(-5.f, -0.3f, -5.f);

	glTexCoord2f(0., 1.);
	glVertex3f(-2.85f, -0.3f, -5.f);


	////botton


	// Front face  
	glTexCoord2f(0., 0.);
	glVertex3f(-2.85f, -0.3f, -5.f);

	glTexCoord2f(1., 0.);
	glVertex3f(-2.85f, -1.3f, -5.f);

	glTexCoord2f(1., 1.);

	glVertex3f(-5.f, -1.3f, -5.f);
	glTexCoord2f(0., 1.);
	glVertex3f(-5.f, -0.3f, -5.f);


	// Left face 
	

	glVertex3f(-2.85f, -1.3f, -5.0f);
	glTexCoord2f(0., 0.);

	glVertex3f(-2.6f, 0.6f, -6.5f);
	glTexCoord2f(1., 0.);

	glVertex3f(-2.6f, 1.6f, -6.5f);//

	glTexCoord2f(1., 1.);
	glVertex3f(-2.85f, -0.3f, -5.f);//

	glTexCoord2f(0., 1.);

	glEnd();
	glDisable(GL_TEXTURE_2D);


}

void renderland() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureland);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS);
	glTexCoord2f(0., 0.);
	glVertex3f(-5, -1.3, -5);


	glTexCoord2f(1., 0.);
	glVertex3f(5, -1.3, -5);

	glTexCoord2f(1., 1.);
	glVertex3f(5, -1.3, -3);

	glTexCoord2f(0., 1.);
	glVertex3f(-5, -1.3, -3);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}