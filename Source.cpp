#include <iostream>
#include "racket.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4.6);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4.6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(2560, 1440, "Pong", NULL, NULL);
	if (window == NULL)
	{
		std::cout << " erreur lors de la generation de la fenetre " << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialise glad " << std::endl;
		return-1;
	}
	glViewport(0, 0, 2560, 1440);
	racket racketBall;
	float dirMoveRacket1Y = 0.0f, dirMoveRacket2Y = 0.0f;
	racketBall.setBufferRacket1();
	racketBall.setBufferRacket2();
	while (!glfwWindowShouldClose(window))
	{
		std::cout << dirMoveRacket1Y << std:: endl;
		if (dirMoveRacket1Y <= 1.0f - (0.5/2) && dirMoveRacket1Y >= -1.0f + 0.5/2)
		{
			dirMoveRacket1Y = dirMoveRacket1Y + racketBall.moveRacket1(window, dirMoveRacket1Y);
		}
		else if (dirMoveRacket1Y > 1.0f - (0.5/2)) {
			if (racketBall.buttonRacket1_down(window) == true) {
				dirMoveRacket1Y += -0.010f;
			}
		}
		else if (dirMoveRacket1Y < -1.0f + 0.5 /2) {
			if (racketBall.buttonRacket1_up(window) == true) {
				dirMoveRacket1Y += 0.010f;
			}
		}
		if (dirMoveRacket2Y <= 1.0f - (0.5 / 2) && dirMoveRacket2Y >= -1.0f + 0.5 / 2)
		{
			dirMoveRacket2Y = dirMoveRacket2Y + racketBall.moveRacket2(window, dirMoveRacket2Y);
		}
		else if (dirMoveRacket2Y > 1.0f - (0.5 / 2)) {
			if (racketBall.buttonRacket2_down(window) == true) {
				dirMoveRacket2Y += -0.010f;
			}
		}
		else if (dirMoveRacket2Y < -1.0f + 0.5 / 2) {
			if (racketBall.buttonRacket2_up(window) == true) {
				dirMoveRacket2Y += 0.010f;
			}
		}
		glUniform1f(glGetUniformLocation(racketBall.getShaderProgram2(), "dirMoveRacket2Y"), dirMoveRacket2Y);
		glUniform1f(glGetUniformLocation(racketBall.getShaderProgram(), "dirMoveRacket1Y"), dirMoveRacket1Y);
		process_input(window);
		glClearColor(0.9f, 0.5f, 0.2f, 0.9f);
		glClear(GL_COLOR_BUFFER_BIT);
		racketBall.drawRacket2();
		racketBall.drawRacket1();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	racketBall.~racket();
}