#include <stdio.h>
#include <string.h>
#include "gldeps.h"

GLuint shaderprogram;
const char *shadersrc;
char shaderstr[1001];

const char *vertexsource = R"glsl(
#version 330
layout(location = 0) in vec3 position;

void main() {
gl_Position = vec4(position, 1.0);
}

)glsl";

const char *fragmentsource = R"glsl(
#version 330
out vec4 outColor;
const vec4 color1 = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 color2 = vec4(0.0f, 1.0f, 0.0f, 1.0f);
void main() {
outColor = mix(color1, color2, 0.5);
}
)glsl";


int exitwerror(char *errmsg) {
printf("error: %s\n", errmsg);
exit(1);
}

 
int getshader(char *shader) {
int count;
char shadernamebuf[100] = "shaders/";
FILE *f = fopen(strcat(shadernamebuf, shader), "r");
if (!f) exitwerror("unable to open shader file");
count = fread(shaderstr, 1, 1000, f);
shadersrc = (char*) malloc(count+1);
shadersrc = shaderstr;
fclose(f);
return count;
}




int createprogram(char *tocreate) {
GLuint fragmentshader, vertexshader;
GLint status;
vertexshader = glCreateShader(GL_VERTEX_SHADER);
getshader(tocreate);
glShaderSource(vertexshader, 1, &shadersrc, NULL);
glCompileShader(vertexshader);
glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &status);
if (status == GL_FALSE) exitwerror("Unable to compile vertex shader!");
fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentshader, 1, &fragmentsource, NULL);
glCompileShader(fragmentshader);
glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &status);
if (status == GL_FALSE) {
printf("Unable to compile fragment shader!\n");
exit(1);
}

shaderprogram = glCreateProgram();
glAttachShader(shaderprogram, vertexshader);
glAttachShader(shaderprogram, fragmentshader);
glLinkProgram(shaderprogram);


glUseProgram(shaderprogram);


glGetProgramiv(shaderprogram, GL_LINK_STATUS, &status);
if (status == GL_FALSE) {
printf("link error!\n");
exit(1);
}

glDetachShader(shaderprogram, vertexshader);
glDetachShader(shaderprogram, fragmentshader);
glDeleteShader(fragmentshader);
glDeleteShader(vertexshader);
return shaderprogram;
}



