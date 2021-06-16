#include <iostream>
#include "glut.h"
#include <cmath>
#include <windows.h>
const float arrow = 10.0;
const float pi = 3.14159265359;
const float angleSec = 2 * pi / 60;
const float angleMin = 2 * pi / 60;
const float angleH = 2 * pi / 12;
int hour, minute, second = 0;
SYSTEMTIME t;

void drawClock(int hour, int min, int second) {
	float theta;
	int posX = 0;
	int posY = 0;
	int radio = 9;
	glColor3f(0.0, 0.4, 0.2);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * 3.1416 / 180;
		glVertex2f(posX + radio * cos(theta), posY + radio * sin(theta));
	}
	glEnd();
	
	
	glColor3f(1, 1, 1);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(0.4, 0.5 + 6.5);
	glVertex2f(0.4, -0.5 + 6.5);
	glVertex2f(0.2, 0.5 + 6.5);
	glVertex2f(0.2, -0.5 + 6.5);

	
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2f(0-0.2, -0.5 + 6.5);
	glVertex2f(-0.2 - 0.2, 0.5 + 6.5);
	glVertex2f(-0.2 - 0.2, -0.5 + 6.5);
	glVertex2f(0 - 0.2, 0.5 + 6.5);

	glVertex2f(0+0.2, -0.5 - 6.5);
	glVertex2f(-0.1, 0.5 - 6.5);
	glVertex2f(0 + 0.2, -0.5 - 6.5);
	glVertex2f(0.5 , 0.5 - 6.5);
	glVertex2f(0 - 0.2, -0.5 - 6.5);
	glVertex2f(0 - 0.2, 0.5 - 6.5);

	glVertex2f(6.5, 0.5);
	glVertex2f(6.5, -0.5);
	glVertex2f(6.3, 0.5);
	glVertex2f(6.3, -0.5);
	glVertex2f(6.1, 0.5);
	glVertex2f(6.1, -0.5);

	glVertex2f(0 - 6.4, -0.5);
	glVertex2f(- 0.2 - 6.4, 0.5 );
	glVertex2f( - 0.2 - 6.4, -0.5 );
	glVertex2f(0- 6.4, 0.5 );

	glVertex2f( - 6.75, -0.5);
	glVertex2f( - 6.75 , 0.5);

	glEnd();
	
	glColor3f(0, 0, 0);
	glLineWidth(3);
	for (float phi = 0.0; phi <= 2 * pi; phi += pi / 6) {
		glBegin(GL_LINES);
		glVertex2f(arrow * 0.7 * cos(phi), arrow * 0.7 * sin(phi));
		glVertex2f(arrow * 0.9 * cos(phi), arrow * 0.9 * sin(phi));
	}
	glEnd();
	
	glColor3f(0, 0, 0);
	glLineWidth(3);
	for (float phi = 0.0; phi <= 2 * pi; phi += pi / 30) {
		glBegin(GL_LINES);
		glVertex2f(arrow * 0.76 * cos(phi), arrow * 0.76 * sin(phi));
		glVertex2f(arrow * 0.9 * cos(phi), arrow * 0.9 * sin(phi));
	}
	glEnd();

	
	glColor3f(0, 0, 0);
	glLineWidth(30);
	glBegin(GL_LINE_STRIP);
	for (float phi = 0.0; phi < 2 * pi; phi += pi /100) {
		glVertex2f(9 * cos(phi), 9 * sin(phi));
		glVertex2f(9 * cos(phi + pi/100), 9 * sin(phi + pi/100));
	}
	glEnd();
	
	
	glColor3f(1, 0, 0); 
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(-1 * arrow * 0.55 * -cos((second - 15) * angleSec), -1 * arrow * 0.55 * sin((second - 15) * angleSec));
	glEnd();



	glColor3f(0, 1, 0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(-1 * arrow * 0.57 * -cos((minute - 15) * angleMin), -1 * arrow * 0.57 * sin((minute - 15) * angleMin));
	glEnd();

	glColor3f(1, 0, 0.7);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 0);
	glVertex2f(  arrow * 0.3 * cos((hour - 15) * angleH), -1 * arrow * 0.3 * sin((hour - 15) * angleH));
	glEnd();
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	drawClock(hour, minute, second);

	glutSwapBuffers();
}


void myInit() {
	glClearColor(255, 255, 255, 0); 
	glPointSize(5); 
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	GetLocalTime(&t);
	second = t.wSecond;
	minute = t.wMinute;
	hour = t.wHour;
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 640);
	glutCreateWindow("Lab6");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / 60, timer, 0);
	myInit();
	glutMainLoop();
}