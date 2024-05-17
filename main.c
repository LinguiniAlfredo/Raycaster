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

int mapX=8, mapY=8, mapS=64;
int map[] = {
    1,1,1,1,1,1,1,1,
    1,0,0,1,0,0,0,1,
    1,0,0,1,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,
};

void drawMap2D() {
    int x, y, xOffset, yOffset;
    for (x=0; x < mapX; x++) {
        for (y=0; y < mapY; y++) {

            if (map[y * mapX + x] == 1) {
                glColor3f(1,1,1);
            } else {
                glColor3f(0,0,0);
            }

            xOffset = x * mapS;
            yOffset = y * mapS;

            glBegin(GL_QUADS);
            glVertex2i(xOffset + 1, yOffset + 1);
            glVertex2i(xOffset + 1, yOffset + mapS - 1);
            glVertex2i(xOffset + mapS - 1, yOffset + mapS - 1);
            glVertex2i(xOffset + mapS - 1, yOffset + 1);
            glEnd();
        }
    }
    
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
    drawMap2D();
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
