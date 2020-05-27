#include "Window.h"

#include <iostream>

#define Print(x) std::cout << x 
#define Error(x) std::cerr << x 

Window::Window(const std::string& title, int width, int height)
	: m_Title(title), m_Width(width), m_Height(height)
{
	if (!glfwInit())
		Error("Error initializng glfw!\n");

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);

	if (!m_Window)
	{
		Error("Error creating window!\n");
		glfwTerminate();
	}

	m_Data.Title = m_Title;
	m_Data.width = m_Width;
	m_Data.height = m_Height;

	glfwSetWindowUserPointer(m_Window, &m_Data);

	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			int correction;
			int vwidth = 400;
			int vheight = 240;

			glViewport(0, 0, width, height);


			float deviceRatio = width / height;
			float virtualRatio = vwidth / vheight;
			float xCorrection = width / vwidth;
			float yCorrection = height / vheight;

			if (virtualRatio < deviceRatio) {
				correction = yCorrection;
			}
			else {
				correction = xCorrection;
			}
			float left = -width / 2.0f / correction;
			float right = width / 2.0f / correction;
			float bottom = -height / 2.0f / correction;
			float top = height / 2.0f / correction;
		});
	glfwMakeContextCurrent(m_Window);

	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GL_MAJOR_VERSION, 3);
	glfwWindowHint(GL_MINOR_VERSION, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(m_Window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);
}

GLFWwindow* Window::GetWindow()
{
	return m_Window;
}