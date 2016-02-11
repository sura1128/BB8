// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

using namespace std;

float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;
float red = 1.0, blue = 1.0, green = 1.0;
float x = 4.0;
float y = 40.0;
float roll = 0.0;

// Helper Functions

void doTransforms(float sX, float sY, float sZ, float tX, float tY, float tZ, int degrees) {
	glScalef(sX, sY, sZ);
	glTranslatef(tX, tY, tZ);
}

void setColours(float R, float G, float B) {
	glColor3f(R, G, B);
}

// Basic Shape Functions - Circle, Ring, Quadrilateral, Rectangle

void drawCircle(float sX, float sY, float sZ, float tX, float tY, float tZ, int degrees, float R, float G, float B) {
	
	doTransforms(sX, sY, sZ, tX, tY, tZ, 0);
	setColours(R, G, B);
	
	const float PI = 3.14159 / 180;
	
	glBegin(GL_POLYGON);
	for (int i = 0; i < degrees; i++) {
		float rad = i*PI;
		glVertex2f(cos(rad) * 5, sin(rad) * 5);
	}
	glEnd();
}

void drawQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

void drawLine(float xStart, float yStart, float xEnd, float yEnd, float R, float G, float B) {
	glColor3f(R, G, B);
	glBegin(GL_LINE_STRIP);
	glVertex2f(xStart, yStart);
	glVertex2f(xEnd, yEnd);
	glEnd();
}


void drawRing(float sX, float sY, float sZ, float tX, float tY, float tZ, int degrees, float R, float G, float B) {

	doTransforms(sX, sY, sZ, tX, tY, tZ, 0);
	setColours(R, G, B);

	const float PI = 3.14159 / 180;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < degrees; i++) {
		float rad = i*PI;
		glVertex2f(cos(rad) * 5, sin(rad) * 5);
	}
	glEnd();
}

void drawArc(float sX, float sY, float sZ, float tX, float tY, float tZ, int degrees, float R, float G, float B) {

	doTransforms(sX, sY, sZ, tX, tY, tZ, 0);
	setColours(R, G, B);

	const float PI = 3.14159 / 180;

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < degrees; i++) {
		float rad = i*PI;
		glVertex2f(cos(rad) * 5, sin(rad) * 5);
	}
	glEnd();
}

// Some modified shape functions for texturing

void drawHorizontalRec(float sX, float sY, float sZ, float tX, float tY, float tZ, int degrees, float R, float G, float B) {
	doTransforms(sX, sY, sZ, tX, tY, tZ, degrees);
	setColours(R, G, B);
	drawQuad(-4.2, 1, 3, 1, 3, -1, -4.3, -1);
}

void drawVerticalRec(float sX, float sY, float sZ, float tX, float tY, float tZ, int degrees, float R, float G, float B) {
	doTransforms(sX, sY, sZ, tX, tY, tZ, degrees);
	setColours(R, G, B);
	drawQuad(-1, -1, -1, 1, 1, 1, 1, -1);
}

void drawBodyCircle(float tX, float tY, float tZ, float degrees, float arcDeg) {
	glPushMatrix();
	glTranslatef(tX, tY, tZ);
	glRotatef(degrees, 0, 0, 1);
	drawCircle(1, 1, 1, 0, 0, 0, arcDeg, 1, 0.5, 0);
	glPopMatrix();
}

void drawQuarter(float tX, float tY, float tZ, float R, float G, float B, float degrees) {
	glColor3f(R, G, B);
	glTranslatef(tX, tY, tZ);
	glRotatef(degrees, 0, 0, 1);
	drawQuad(-1, 2, -0.5, 0, 0.5, 0, 1, 2);
}

void drawOrangeQuads(float tX, float tY, float tZ, int degrees) {
	glPushMatrix();
	drawQuarter(tX, tY, tZ, 1, 0.5, 0, degrees); //orange quad
	glPopMatrix();
}

void drawGreyRing(float tX, float tY, float tZ) {
	glPushMatrix();
	glTranslatef(tX, tY, tZ);
	drawRing(0.03, 0.03, 0.03, 0, 0, 0, 360, 0.7, 0.7, 0.7);
	glPopMatrix();
}


void drawGreyQuads() {
	glPushMatrix();
	glScalef(1.5, 1.5, 0);
	glColor3f(0.7, 0.7, 0.7);
	glRotatef(90, 0, 0, 1);
	drawQuad(-1.7, 2.5, -0.5, 0, 0.5, 0, 1.7, 2.5); //grey quad
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glRotatef(-75, 0, 0, 1);
	glTranslatef(0, 3, 0);
	drawQuad(-1.5, 1.5, -1, 0, 1, 0, 1.5, 1.5); //grey quad
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.7, 0.7);
	glRotatef(185, 0, 0, 1);
	glTranslatef(0, 3, 0);
	drawQuad(-1.5, 1.5, -1, 0, 1, 0, 1.5, 1.5); //grey quad
	glPopMatrix();
}

void drawGreyLines() {
	glPushMatrix();
	glTranslated(0.5, 0, 0);
	glRotatef(60, 0, 0, 1);
	drawLine(0, 6.5, 0, 14.5, 0.7, 0.7, 0.7); //lines
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0, 0);
	glRotatef(120, 0, 0, 1);
	drawLine(0, 6.5, 0, 17, 0.7, 0.7, 0.7);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0, 0);
	glRotatef(-60, 0, 0, 1);
	drawLine(0, 5.8, 0, 6.6, 0.7, 0.7, 0.7);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 0, 0);
	glRotatef(-170, 0, 0, 1);
	drawLine(0, 6.2, 0, 11.8, 0.7, 0.7, 0.7);
	glPopMatrix();
}

// Elements of BB8 = signal, antenna, head, eye, face decor, neck, body, body decor

void drawSignal() {
	glPushMatrix();
	drawArc(0.2, 0.2, 0.2, x, y, 0, 40, red, green, blue);
	glPopMatrix();
	glPushMatrix();
	drawArc(0.2, 0.2, 0.2, x+2, y+1, 0, 50, red, green, blue);
	glPopMatrix(); 
	glPushMatrix();
	drawArc(0.2, 0.2, 0.2, x+4, y+2, 0, 60, red, green, blue);
	glPopMatrix();
}

void drawAntenna() {
	glPushMatrix();
	drawLine(0.9, 5.7, 0.9, 7.8, 0.7, 0.7, 0.7);
	drawLine(0.4, 5.7, 0.4, 7.3, 1, 1, 1);
	glPopMatrix();
}

void drawHead() {
	glPushMatrix();
	drawCircle(0.6, 0.6, 0.6, 0, 4.8, 0, 181, 0.9, 0.9, 0.9);
	glPopMatrix();
}

void drawEye() {
	glPushMatrix();
	drawCircle(0.14, 0.14, 0.14, 0, 32, 0, 360, 0, 0, 0);
	drawCircle(0.4, 0.4, 0.4, -3.5, 3, 0, 360, 0.9, 0.9, 0.9);
	glPopMatrix();
}

void drawHeadRings() {
	setColours(0.7, 0.7, 0.7);
	drawQuad(-1.3, 5.6, -1.8, 5.3, 1.8, 5.3, 1.3, 5.6);
	setColours(1, 0.5, 0);
	drawQuad(-2.1, 5, -2.3, 4.8, -0.7, 4.8, -0.6, 5);
	drawQuad(0.6, 5, 0.7, 4.8, 2.3, 4.8, 2.1, 5);
}

void drawFaceDecor() {
	glPushMatrix();
	drawCircle(0.08, 0.08, 0.08, 18, 45, 0, 360, 0.5, 0.5, 0.5);
	glPopMatrix();

	glPushMatrix();
	drawCircle(0.04, 0.04, 0.04, 38, 90, 0, 360, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	drawHorizontalRec(0.2, 0.2, 0.2, -10.7, 15.5, 0, 0, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	drawVerticalRec(0.2, 0.2, 0.2, -5, 15.5, 0, 0, 1, 0.5, 0);
	glPopMatrix();

	glPushMatrix();
	drawRing(0.04, 0.04, 0.04, 0, 82, 0, 360, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	drawRing(0.05, 0.05, 0.05, 0, 65.6, 0, 360, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	drawHeadRings();
	glPopMatrix();
}

void drawCollar(float R, float G, float B) {
	setColours(R, G, B);
	drawQuad(-3, 0.2, -3, 0, 3, 0, 3, 0.2);
}

void drawNeckline(float R, float G, float B) {
	setColours(R, G, B);
	drawQuad(-3, 0, -3, -0.2, 3, -0.2, 3, 0);
	drawQuad(-2.8, -0.2, -2.8, -0.4, 2.8, -0.4, 2.8, -0.2);

}

void drawNeck(float tX, float tY, float tZ) {
	glPushMatrix();
	doTransforms(1, 1, 1, tX, tY, tZ, 0);

	glPushMatrix();
	drawCollar(0.7, 0.7, 0.7);
	glPopMatrix();

	glPushMatrix();
	drawNeckline(0.9, 0.9, 0.9);
	drawLine(-2.8, -0.4, 2.8, -0.4, 0, 0, 0);
	glPopMatrix();

	glPopMatrix();
}

void drawBody() {
	glPushMatrix();
	drawCircle(1, 1, 1, 0, -2, 0, 360, 0.9, 0.9, 0.9);
	glPopMatrix();
}


void drawBodyDecor() {
	//orange circle
	glPushMatrix();
	drawCircle(0.5,0.5,0.5, 4, -2, 0, 360, 1, 0.5, 0);
	glPopMatrix();

	//side orange circles 
	glPushMatrix();
	drawBodyCircle(0, -2, 0, 180, 60);
	drawBodyCircle(0, -2, 0, 120, 40);
	drawBodyCircle(0, -2, 0, 270, 50);
	glPopMatrix();

	// details inside orange circle
	glPushMatrix();
		drawCircle(0.4, 0.4, 0.4, 5, -2.5, 0, 360, 0.9, 0.9, 0.9); //white circle
		
		drawOrangeQuads(2,2.5,0,-45); //orange quads
		drawOrangeQuads(-2, 2.5, 0, 45);
		drawOrangeQuads(2,2.5,0,-45);
		drawOrangeQuads(-2,2.5,0,45);

		glPushMatrix();
		glRotatef(90, 0, 0, 1);
		drawCircle(0.5, 0.5, 0.5, 0, 0, 0, 181, 0.7, 0.7, 0.7); //grey circle
		glPopMatrix();

		glPushMatrix();
		glRotatef(-90, 0, 0, 1);
		drawRing(0.5, 0.5, 0.5, 0, 0, 1, 181, 0.7, 0.7, 0.7); //grey rings
		drawRing(0.45, 0.45, 0.45, 0, 0, 0, 181, 0.7, 0.7, 0.7); //grey rings
		glPopMatrix();

		drawGreyQuads();
		drawGreyLines();		

		//Square strip 
		glPushMatrix();
		glTranslatef(-11, -1.5, 0);
		glColor3f(0.7, 0.7, 0.7);
		glBegin(GL_LINE_STRIP); 
		glVertex2f(5, 3);
		glVertex2f(4, 3);
		glVertex2f(4, 0);
		glVertex2f(5, 0);		
		glEnd();
		glPopMatrix();
	
	glPopMatrix();

	drawGreyRing(-2,0,0);
	drawGreyRing(-1,-4,0);
	drawGreyRing(0,2,0);
	drawGreyRing(-4,-1,0);
	drawGreyRing(-2,-2,0);
	drawGreyRing(2,-4,0);
	drawGreyRing(4,-3,0);
	drawGreyRing(3,1.5,0);
	drawGreyRing(0,-6,0);
}


void drawBB8() {
	drawSignal();
	drawHead();
	drawFaceDecor();	
	drawEye();
	drawAntenna();
	drawBody();
	drawBodyDecor();
	drawNeck(0, 2.7, 0);
	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();

	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);
	
	drawBB8();
	//draw your stuff here
	glPopMatrix();
	glFlush ();
}



void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glShadeModel (GL_SMOOTH);
}



void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

		case 'a':
			alpha+=10;
			glutPostRedisplay();
		break;

		case 'd':
			alpha-=10;
			glutPostRedisplay();
		break;

		case 'q':
			k+=0.1;
			glutPostRedisplay();
		break;

		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
		break;

		case 'z':
			tx-=0.1;
			glutPostRedisplay();
		break;

		case 'c':
			tx+=0.1;
			glutPostRedisplay();
		break;

		case 's':
			ty-=0.1;
			glutPostRedisplay();
		break;

		case 'w':
			ty+=0.1;
			glutPostRedisplay();
		break;
		// emit signal
		case 'j':
			if (red == 1.0 && green == 1.0 && blue == 1.0) {
				red = 0.0;
				green = 0.0;
				blue = 0.0;
			}
			else {
				red = 1.0;
				blue = 1.0;
				green = 1.0;
			} 
			glutPostRedisplay();
		break;
			
		case 'x':
			x = 15;
			y = 81;
			glutPostRedisplay();
		break;

		case 27:
			exit(0);
		break;


		default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 1\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";
	cout <<"ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
