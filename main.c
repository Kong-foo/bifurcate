/*
errorcb - error callback
keycb - keyboard callback
init - initialize window
setupbuffers - setup buffers and buffer format
display - make the call to draw
createprogram("<name>") - create program from shader file shaders/<name>
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include "gldeps.h"
#define true 1
#define false 0
//#include "shaderstuff.h"
int createprogram();

#define BUFFERSIZE 2048
#define ARRAYSIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
typedef int bool;


float fbuf[BUFFERSIZE];
int fbufsize;

GLFWwindow* window;
GLuint vertexbuffer;

int mainprog;

void display(void);



void errorcb(int error, const char* description) {
printf("%d %s\n", error, description);
fflush(stdout);
}

void keycb (GLFWwindow* window, int key, int scancode, int action, int mods) {
switch (key) {
case 81:
glfwSetWindowShouldClose(window, GLFW_TRUE);
break;
case GLFW_KEY_RIGHT:
break;
case GLFW_KEY_LEFT:
break;
case GLFW_KEY_UP:
break;
case GLFW_KEY_DOWN:
break;
}

if (key == 32 && action == GLFW_PRESS);
else if (key == 32 && action == GLFW_RELEASE);
}


int init() {

glfwSetErrorCallback(errorcb);
if (!glfwInit()) return 1;

glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

window = glfwCreateWindow(640, 480, "GLSL test", NULL, NULL);
glfwMakeContextCurrent(window);
glfwSetKeyCallback(window, keycb);
glfwSwapInterval(1);
glewInit();
//glEnable(GL_CULL_FACE);
//glCullFace(GL_BACK);
//glFrontFace(GL_CW);
return 0;

}


GLuint vao;
int setupbuffers() {

GLint posattrib;

/*
float l = -1.0;
float r = 1.0;
float b = -1.0;
float t = 1.0;
float n = 0.0;
float f = 1.0;
*/

/*GLfloat orthoprojection[16] = {
2/(r-l), 0, 0, -(r+l)/(r-l),
0, 2/(t-b), 0, -(t+b)/(t-b),
0, 0, -2/(f-n), -(f+n)/(f-n),
0, 0, 0, 1
};*/

//make vertex array
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);

//make vertex buffer
glGenBuffers(1, &vertexbuffer);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

//set data
glBufferData(GL_ARRAY_BUFFER, sizeof(fbuf), fbuf, GL_STATIC_DRAW);

//vertex attributes go in posattrib
posattrib = glGetAttribLocation(mainprog, "position");
glEnableVertexAttribArray(posattrib);

//data goes in the form {<x,y>, <x,y>, <x,y>...}
glVertexAttribPointer(posattrib,2,GL_FLOAT, GL_FALSE, 0,0);

display();

//GLint colorattrib = glGetAttribLocation(transprog, "color");
return 0;
}


void display() {

glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
glClear(GL_COLOR_BUFFER_BIT);
glDrawArrays(GL_LINE_STRIP, 0, fbufsize);

glUseProgram(mainprog);
glBindVertexArray(vao);
glfwSwapBuffers(window);
}


void idle() {
double time, delta;
static double oldtime = 0;
time = glfwGetTime();
delta = (time - oldtime)/1000;


oldtime = time;
}


int main(int argc, char **argv) {

float cube[] = {
-0.2, -0.2,
-0.2, 0.2,
0.2, 0.2
};


memcpy(fbuf, cube, sizeof(cube));
fbufsize = sizeof(cube);
init();
mainprog = createprogram("point.v");
setupbuffers();


//glfwSwapBuffers(window);
while (glfwWindowShouldClose(window) != 1) {
glfwPollEvents();
idle();
usleep(10000);
}

glDeleteProgram(mainprog);
glDeleteBuffers(1, &vertexbuffer);
glfwDestroyWindow(window);
glfwTerminate();



return 0;
}
