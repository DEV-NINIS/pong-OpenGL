#include "racket.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stbi_img.h"
float racket::verteciesRacket1[] = {
	-0.0f, -0.5f, 0.0f,      0.9f, 0.8f, 0.1f,		0.5f, 0.25f,
		-0.0f, 0.5f, 0.0f,		0.9f, 0.5f, 0.9f,	0.5f, 0.75f,
		-0.5f, 0.5f, 0.0f,		0.5f, 0.9f, 0.7f,	0.25f, 0.75f,
		-0.5f, -0.5f, 0.0f,		0.4f, 0.2f, 0.1f,	0.25f, 0.25f
};
float racket::textCords[] = {
	0
};
float racket::verteciesRacket2[] = {
	// position			// color					//texCoord
	0.95f, -0.25f, 0.0f,	0.9f, 0.8f, 0.1f,		0.975f, 0.5f, 
	0.95f, 0.25f, 0.0f,		0.6f, 0.5f, 0.1f,		0.975f, -0.5f,
	0.92f, 0.25f, 0.0f,		0.5f, 0.9f, 0.7f,		0.95f, -0.5f,
	0.92f, -0.25f, 0.0f,	0.1f, 0.2f, 0.9f,		0.95f, 0.5f
};
unsigned int racket::indexRacket1[] = {
	0, 1, 2,	// first triangle
};
racket::racket() {
	fragShader;
	vertexShader; 
	programShader;
	codeFragmentShader = "#version 460 core\n"

"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D ourTexture;\n"

"void main()\n"
"{\n"
"   FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);\n"
"}\n\0";

	codeVertexShader = "#version 460 core\n"

		"layout (location = 0) in vec3 aPos;\n" // la variable position a l'attribut de position 0
		"layout (location = 1) in vec3 aColor;\n"
		"layout (location = 2) in vec2 aTexCoord;\n"

		"uniform float dirMoveRacket1Y;\n"
		"out vec3 ourColor;\n" // nous definirons la couleur dans cette variable 
		"out vec2 TexCoord;\n"

		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y + dirMoveRacket1Y, aPos.z, 1.0);\n"
		"   ourColor = aColor;\n"
		"   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
		"}\n\0";
	//
	codeVertexShader2 = "#version 460 core\n"

		" layout (location = 2) in vec3 aPos;\n"
		" layout (location = 3) in vec3 aColor;\n"
		"uniform float dirMoveRacket2Y;\n"
		" out vec3 aColor2;\n"

		"void main() {\n"
		
		"	gl_Position = vec4(aPos.x, aPos.y + dirMoveRacket2Y, aPos.z, 1.0);\n"
		
		
		"	aColor2 = vec3(aColor);\n"
		"}\n";
	codeFragmentShader2 = "#version 460 core\n"

		"in vec3 aColor2;\n"
		"void main() {\n"

		"FragColor = vec4(aColor2.x, aColor2.y, aColor2.z, 1.0);\n"
		""
		"}\n";
	successCompile;
	texCoordRacket1; texCoordRacket2;
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenTextures(1, &texCoordRacket1);
	glBindTexture(GL_TEXTURE_2D, texCoordRacket1);
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	int nrChanels, width, height;
	unsigned char* data = stbi_load("img/containerBois.jpg", &width, &height, &nrChanels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << " erreur lors du load des textures " << std::endl;
	}
	stbi_image_free(data);

	// fin de la compillation des  shaders 

}
void racket::drawRacket1() {
	glUseProgram(programShader);
	glBindTexture(GL_TEXTURE_2D, texCoordRacket1);
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
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		return true;
	}
	else {
		return false;
	}
}
bool racket::buttonRacket2_down(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
		return true;
	}
	else {
		return false;
	}
}
GLuint racket::getShaderProgram() { return programShader; }
GLuint racket::getShaderProgram2() { return programShader2; }