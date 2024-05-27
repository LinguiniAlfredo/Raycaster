#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535

const int WIDTH = 1024;
const int HEIGHT = 512;

float px, py, pdx, pdy, pa;


void drawPlayer() {
	glColor3f(1,1,0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(px, py);
	glEnd();

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px + pdx * 5, py + pdy * 5);
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
	if(key=='a') {
        pa -= 0.1;
        if (pa < 0) {
            pa += 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
	}
	if(key=='d'){
        pa += 0.1;
        if (pa < 0) {
            pa -= 2 * PI;
        }
        pdx = cos(pa) * 5;
        pdy = sin(pa) * 5;
	}
	if(key=='w'){
        px += pdx; py += pdy;
	}
	if(key=='s'){
        px -= pdx; py -= pdy;
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
	px = 300; 
	py = 300;
    pdx = cos(pa) * 5;
    pdy = sin(pa) * 5;
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
