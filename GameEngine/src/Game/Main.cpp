#include <iostream>

#define GLEW_STATIC

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Shader.h"
#include "Window.h"

int main()
{
	Window window = Window("New Game", 800, 600);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing glew!\n";
		return -1;
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GL_MAJOR_VERSION, 3);
	glfwWindowHint(GL_MINOR_VERSION, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(window.GetWindow(), (vidmode->width - window.GetWidth()) / 2, (vidmode->height - window.GetHeight()) / 2);

	uint32_t m_VAO, m_VBO, m_IBO;

	float vertices[2 * 4] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f, 
		-0.5f, 0.5f,
	};

	int indices[] = { 0,1,2,2,3,0 };

	Shader m_Shader = Shader("src/resources/shaders/basic.glsl");
	m_Shader.Bind();

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

	glm::vec3 m_Position = glm::vec3(0, 0, -3);

	//glm::mat4 m_ViewProjection = glm::ortho(-(width / 2.0f), (width / 2.0f), -(height / 2.0f), (height / 2.0f), 0.1f, 1000.0f);
	glm::mat4 m_ViewProjection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 1.0f, 1000.0f);
	m_Shader.SetMat4("u_ViewProjection", m_ViewProjection);

	glm::mat4 m_Transformation = glm::mat4(1.0f);
	m_Transformation = glm::translate(m_Transformation, m_Position);
	//m_Transformation = glm::scale(m_Transformation, glm::vec3(4.0f, 3.0f, 1.0f));

	m_Shader.SetMat4("u_Transformation", m_Transformation);

	glfwSwapInterval(1);
	glfwShowWindow(window.GetWindow());

	glViewport(0, 0, window.GetWidth(), window.GetHeight());

	while (!glfwWindowShouldClose(window.GetWindow()))
	{

		/*some type of tick system
		poll input
		while not ready to render
		update
		when ready
		render


		*/

		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader.Bind();

		int x = 0;
		int y = 0;

		if (glfwGetKey(window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
			y = 1;
		else if (glfwGetKey(window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
			y = -1;

		if (glfwGetKey(window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
			x = 1;
		else if (glfwGetKey(window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
			x = -1;

		m_Position.x =  x * 0.05;
		m_Position.y =  y * 0.05;
		m_Position.z = 0;

		m_Transformation = glm::translate(m_Transformation, m_Position);
		//m_Transformation = glm::scale(m_Transformation, glm::vec3(1.0f, 1.0f, 1.0f));
		m_Shader.SetMat4("u_ViewProjection", m_ViewProjection);
		m_Shader.SetMat4("u_Transformation", m_Transformation);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window.GetWindow());

		glfwPollEvents();

		glBindVertexArray(0);
		m_Shader.Unbind();
	}

	glfwTerminate();
	return 0;
}