#include "racket.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float racket::verteciesRacket1[] = {
	-0.95f, -0.25f, 0.0f,      0.9f, 0.8f, 0.1f,
		-0.95f, 0.25f, 0.0f,		0.9f, 0.5f, 0.9f,
		-0.92f, 0.25f, 0.0f,		0.5f, 0.9f, 0.7f,
		-0.92f, -0.25f, 0.0f,		0.4f, 0.2f, 0.1f
};
float racket::verteciesRacket2[] = {
	// position			// color
	0.95f, -0.25f, 0.0f,	0.9f, 0.8f, 0.1f,
	0.95f, 0.25f, 0.0f,		0.6f, 0.5f, 0.1f,
	0.92f, 0.25f, 0.0f,		0.5f, 0.9f, 0.7f,
	0.92f, -0.25f, 0.0f,	0.1f, 0.2f, 0.9f
};
unsigned int racket::indexRacket1[] = {
	0, 1, 2,	// first triangle
};
racket::racket() {
	fragShader;
	vertexShader; 
	programShader;
	codeFragmentShader = "#version 460 core\n"

		" in vec3 aColor2;\n"
		" out vec4 FragColor;\n"

		"void main() {\n"
		"FragColor = vec4(aColor2.x, aColor2.y, aColor2.z, 1.0);\n"
		"}\n";

	codeVertexShader = "#version 460 core\n"

		" layout (location = 0) in vec3 aPos;\n"
		" layout (location = 1) in vec3 aColor;\n"
		"uniform float posRacket;\n"
		" out vec3 aColor2;\n"

		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y + posRacket, aPos.z, 1.0);\n"
		"	aColor2 = vec3(aColor);\n"
		"}\n";
	codeVertexShader2 = "#version 460 core\n"

		" layout (location = 2) in vec3 aPos;\n"
		" layout (location = ) in vec3 aColor;\n"
		"uniform float posRacket2;\n"
		" out vec3 aColor2;\n"

		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y + posRacket2, aPos.z, 1.0);\n"
		"	aColor2 = vec3(aColor);\n"
		"}\n";
	codeFragmentShader2 = "#version 460 core\n"

		"in vec3 aColor2;\n"

		"void main() {\n"

		"FragColor = vec4(aColor2.x, aColor2.y, aColor2.z, 1.0);\n"
		"}\n";
	successCompile;
	VBO_racket1; VAO_racket1; EBO_racket1;
	VAO_racket2; VBO_racket2; EBO_racket2;
}
racket::~racket() {
}
void racket::compileShaderRacket() {
	// compilation du vertexShader
	
}
void racket::setBufferRacket1() {
	unsigned int indexRacket12[] = {
	0, 1, 2,	// first triangle
	0, 2, 3
	};
	std::cout << codeFragmentShader << std::endl;
	std::cout << codeVertexShader << std::endl;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar**)&codeVertexShader, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successCompile);
	if (successCompile == NULL) {
		std::cout << "erreur lors de la compillation des shaders " << std::endl;
	}
	// compillation du fragmentShader
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, (const GLchar**)&codeFragmentShader, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &successCompile);
	if (successCompile == NULL) {
		std::cout << " erreur lors de la compilation du fragment shader" << std::endl;
	}
	programShader = glCreateProgram();
	glAttachShader(programShader, vertexShader);
	glAttachShader(programShader, fragShader);
	glLinkProgram(programShader);
	// fin de la compillation des shaders

	glGenVertexArrays(1, &VAO_racket1);
	glGenBuffers(1, &VBO_racket1);
	glGenBuffers(1, &EBO_racket1);
	glBindVertexArray(VAO_racket1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_racket1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verteciesRacket1), verteciesRacket1, GL_STATIC_DRAW);
	// generation de l'EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_racket1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexRacket12), indexRacket12, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// fin de la compillation des  shaders 

}
void racket::drawRacket1() {
	glUseProgram(programShader);
	glBindVertexArray(VAO_racket1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void racket::setBufferRacket2() {
	unsigned int indexRacket12[] = {
	0, 1, 2,	// first triangle
	0, 2, 3
	};
	vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader2, 1, (const GLchar**)&codeVertexShader2, NULL);
	glCompileShader(vertexShader2);

	fragShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader2, 1, (const GLchar**)&codeFragmentShader2, NULL);
	glCompileShader(fragShader2);

	programShader2 = glCreateProgram();
	glAttachShader(programShader2, vertexShader2);
	glAttachShader(programShader2, fragShader2);
	glLinkProgram(programShader2);
	// the end of compilation of shader

	glGenVertexArrays(1, &VAO_racket2);
	glGenBuffers(1, &VBO_racket2);
	glGenBuffers(1, &EBO_racket2);
	// VAO
	glBindVertexArray(VAO_racket2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_racket2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verteciesRacket2), verteciesRacket2, GL_STATIC_DRAW);
	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_racket2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexRacket12), indexRacket12, GL_STATIC_DRAW);
	// pointer 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);
}
void racket::drawRacket2() {
	glUseProgram(programShader2);
	glBindVertexArray(VAO_racket2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(2);
}
float racket::moveRacket1(GLFWwindow* window, float valueY) {
	if (this->buttonRacket1_up(window) == true) {
		return 0.0150f;
	}
	else if (this->buttonRacket1_down(window) == true) {
		return -0.015f;
	}
	else {
		return 0.0f;
	}
}
float racket::moveRacket2(GLFWwindow* window, float valueY) {
	if (this->buttonRacket2_up(window) == true) {
		return 0.010f;
	}
	if (this->buttonRacket2_down(window) == true) {
		return -0.010f;
	}
	else {
		return 0.0f;
	}
}
bool racket::buttonRacket1_up(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		return true;
	}
	else {
		return false;
	}
}
bool racket::buttonRacket1_down(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		return true;
	}
	else {
		return false;
	}
}
bool racket::buttonRacket2_up(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		return true;
	}
	else {
		return false;
	}
}
bool racket::buttonRacket2_down(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		return true;
	}
	else {
		return false;
	}
}
GLuint racket::getShaderProgram() { return programShader; }
GLuint racket::getShaderProgram2() { return programShader2; }