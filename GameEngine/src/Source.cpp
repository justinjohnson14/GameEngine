#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Shader.h>

#include <iostream>

GLFWwindow* window;

Shader* shader;

int main()
{
	if (!glfwInit())
		std::cerr << "Error: Error initializing glfw!\n";

	std::cout << "Initialized glfw\n";

	window = glfwCreateWindow(800,600,"New Game",nullptr,nullptr);
	std::cout << "Created window\n";

	if (!window)
	{
		std::cerr << "Error creating window!\n";
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GL_MAJOR_VERSION, 3);
	glfwWindowHint(GL_MINOR_VERSION, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	
	GLint glew = glewInit();
	if (glew != GLEW_OK)
		std::cerr << ("Error initializing glew!\n");

	std::cout << "Initialized glew\n";
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	shader = new Shader("src/resources/shaders/Test.glsl");

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1, 0, 0));

	glm::mat4 view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	GLuint vao, vbo, ibo;

	float vertices[] = {
		-0.5f, -0.5, 0.5f,
		0.5f, -0.5, 0.5f,
		0.5f, 0.5, 0.5f,
		-0.5f, 0.5f, 0.5f,

		-0.5f, -0.5, -0.5f,
		0.5f, -0.5, -0.5f,
		0.5f, 0.5, -0.5f,
		-0.5f, 0.5f, -0.5f
	};

	unsigned int indices[] = {
		0,1,2,2,3,0,
		1,5,6,6,2,1,
		3,2,6,6,7,3,
		4,5,1,1,0,5,
		4,0,3,3,7,4,
		5,4,7,7,6,5
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);
	shader->Bind();
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	shader->Unbind();
	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//model = glm::rotate(model, glm::radians(-0.05f), glm::vec3(0, 1, 0));
		//model = glm::rotate(model, glm::radians(-0.05f), glm::vec3(1, 0, 0));
		shader->Bind();
		shader->SetMat4("u_Model", model);
		shader->SetMat4("u_View", view);
		shader->SetMat4("u_Projection", projection);
		glBindVertexArray(vao);
		//You must bind the index buffer before each draw
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		shader->Unbind();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}