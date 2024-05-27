#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535

const int WIDTH = 1024;
const int HEIGHT = 512;

float playerX, playerY, playerDeltaX, playerDeltaY, playerAngle;


void drawPlayer() {
	glColor3f(1,1,0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(playerX, playerY);
	glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(playerX, playerY);
    glVertex2i(playerX + playerDeltaX * 5, playerY + playerDeltaY * 5);
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

void drawRays3D()
{
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo;
}

void controls(unsigned char key, int x, int y) {
	if(key=='a') {
        playerAngle -= 0.1;
        if (playerAngle < 0) {
            playerAngle += 2 * PI;
        }
        playerDeltaX = cos(playerAngle) * 5;
        playerDeltaY = sin(playerAngle) * 5;
	}
	if(key=='d'){
        playerAngle += 0.1;
        if (playerAngle < 0) {
            playerAngle -= 2 * PI;
        }
        playerDeltaX = cos(playerAngle) * 5;
        playerDeltaY = sin(playerAngle) * 5;
	}
	if(key=='w'){
        playerX += playerDeltaX; playerY += playerDeltaY;
	}
	if(key=='s'){
        playerX -= playerDeltaX; playerY -= playerDeltaY;
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
    playerDeltaX = cos(playerAngle) * 5;
    playerDeltaY = sin(playerAngle) * 5;
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("raycaster");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(controls);
	glutMainLoop();
}
