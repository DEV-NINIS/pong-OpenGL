#ifndef DEF_BALL
#define DEF_BALL
#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class ball
{
public:
	ball();
	virtual ~ball();
	void compileShaderBall();
protected:
	int* successCompile;
	GLuint vertexShaderBall;
	GLuint fragmentShaderBall;
	GLuint programShaderBall;
	const char* vertexShaderCode;
	const char* fragmentShaderCode;
	std::vector<float> verteciesBall;
	static unsigned int indexBall[];
};


#endif // !1
