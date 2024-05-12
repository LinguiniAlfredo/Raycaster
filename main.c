#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

const int WIDTH = 1024;
const int HEIGHT = 512;

float playerX, playerY;

void drawPlayer() {
	glColor3f(1,1,0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(playerX, playerY);
	glEnd();
}

void controls(unsigned char key, int x, int y) {
	if(key=='w') {
		playerY -= 5;
	}
	if(key=='a'){
		playerX -= 5;
	}
	if(key=='s'){
		playerY += 5;
	}
	if(key=='d'){
		playerX += 5;
	}
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawPlayer();
	glutSwapBuffers();
}

void init() {
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 512, 0);
	playerX = 300; 
	playerY = 300;
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("raycast test");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(controls);
	glutMainLoop();
}