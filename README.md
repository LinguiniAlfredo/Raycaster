## Install OpenGL libraries with the following:
sudo apt-get install libglew-dev freeglut3-dev mesa-utils

## Compile with the following
gcc -o ./build/main main.c -lglut -lGLU -lGL -lm

