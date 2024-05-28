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
    int ray, mx, my, mp, depthOfField;
    float rayX, rayY, rayAngle, xOffset, yOffset;
    rayAngle = playerAngle;

    // Check horizontal line intersection
    for (ray = 0; ray < 1; ray++) {
        depthOfField = 0;
        float aTan = -1 / tan(rayAngle);
        // looking up
        if (ray > PI) {
            rayY = (((int) playerY >> 6) << 6) - 0.0001;
            rayX = (playerY - rayY) * aTan + playerX;
            yOffset = -64; 
            xOffset = -yOffset * aTan;
        }
        // looking down
        if (ray < PI) {
            rayY = (((int) playerY >> 6) << 6) + 64;
            rayX = (playerY - rayY) * aTan + playerX;
            yOffset = 64; 
            xOffset = -yOffset * aTan;
        }
        // looking left or right
        if (rayAngle == 0 || rayAngle == PI) {
            rayX = playerX;
            rayY = playerY;
            depthOfField = 8;
        }
        while (depthOfField < 8) {
            mx = (int) rayX >> 6;
            my = (int) rayY >> 6;
            mp = my * mapX + mx;

            if (mp < mapX * mapY && map[mp] == 1) {
                depthOfField = 8;
            } else {
                rayX += xOffset;
                rayY += yOffset;
                depthOfField += 1;
            }
        }
        glColor3f(0,1,0);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(playerX, playerY);
        glVertex2i(rayX, rayY);
        glEnd();
    }
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
    drawRays3D();
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
