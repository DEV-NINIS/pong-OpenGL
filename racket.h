#ifndef DEF_RACKET
#define DEF_RACKET
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class racket
{
public:
	racket();
	virtual ~racket();
	void setBufferRacket1();
	void drawRacket1();
	void drawRacket2();
	void setBufferRacket2();
	bool buttonRacket1_up(GLFWwindow* window);
	bool buttonRacket1_down(GLFWwindow* window);
	bool buttonRacket2_up(GLFWwindow* window);
	bool buttonRacket2_down(GLFWwindow* window);
	float moveRacket1(GLFWwindow* window, float valueY);
	float moveRacket2(GLFWwindow* window, float valueY);
	void compileShaderRacket();
	GLuint getShaderProgram();
	GLuint getShaderProgram2();
protected:
	int successCompile;
	const char* codeVertexShader;
	const char* codeVertexShader2;
	const char* codeFragmentShader;
	const char* codeFragmentShader2;
	unsigned int VBO_racket1;
	unsigned int VAO_racket1;
	unsigned int EBO_racket1;
	unsigned int VAO_racket2;
	unsigned int VBO_racket2;
	unsigned int EBO_racket2;
	unsigned int fragShader, fragShader2;
	unsigned int vertexShader, vertexShader2;
	unsigned int programShader;
	unsigned int programShader2;
	GLuint texCoordRacket1;
	GLuint texCoordRacket1_2;
	GLuint texCoordRacket2;
	GLuint tecCoordRacket2_2;
	static float textCords[];
	static float verteciesRacket1[];
	static float verteciesRacket2[];
	static unsigned int indexRacket1[];
};


#endif // !1

