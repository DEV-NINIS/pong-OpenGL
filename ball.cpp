#include "ball.h"
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

ball::ball() {
	successCompile = new int;
	vertexShaderBall; fragmentShaderBall;
	programShaderBall;
	vertexShaderCode;
	fragmentShaderCode;
	verteciesBall;
	indexBall;
}
ball::~ball() {
	delete successCompile;
}
